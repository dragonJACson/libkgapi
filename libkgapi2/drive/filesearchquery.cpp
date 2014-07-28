/*
 * Copyright (C) 2014  Daniel Vrátil <dvratil@redhat.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */

#include "filesearchquery.h"

#include <QString>
#include <QDateTime>

using namespace KGAPI2;
using namespace KGAPI2::Drive;

class FileSearchQuery::Private : public QSharedData
{
public:
    Private();
    Private(const Private &other);
    ~Private();

    static QString fieldToString(Field field);
    static QString compareOperatorToString(CompareOperator op);
    static QString logicOperatorToString(LogicOperator op);
    static QString valueToString(Field field, const QVariant &var);

    QList<FileSearchQuery> subqueries;
    QVariant value;
    Field field;
    CompareOperator compareOp;
    LogicOperator logicOp;
};

FileSearchQuery::Private::Private()
    : QSharedData()
{
}

FileSearchQuery::Private::Private(const Private &other)
    : QSharedData(other)
    , subqueries(other.subqueries)
    , value(other.value)
    , field(other.field)
    , compareOp(other.compareOp)
    , logicOp(other.logicOp)
{
}

FileSearchQuery::Private::~Private()
{
}


QString FileSearchQuery::Private::fieldToString(Field field)
{
    switch (field) {
    case Title:
        return QLatin1String("title");
    case FullText:
        return QLatin1String("fullText");
    case MimeType:
        return QLatin1String("mimeType");
    case ModifiedDate:
        return QLatin1String("modifiedDate");
    case LastViewedByMeDate:
        return QLatin1String("lastViewedByMeDate");
    case Trashed:
        return QLatin1String("trashed");
    case Starred:
        return QLatin1String("starred");
    case Parents:
        return QLatin1String("parents");
    case Owners:
        return QLatin1String("owners");
    case Writers:
        return QLatin1String("writers");
    case Readers:
        return QLatin1String("readers");
    case SharedWithMe:
        return QLatin1String("sharedWithMe");
    }

    Q_ASSERT(false);
    return QString();
}

QString FileSearchQuery::Private::compareOperatorToString(CompareOperator op)
{
    switch (op) {
    case Contains:
        return QLatin1String(" contains ");
    case Equals:
        return QLatin1String(" = ");
    case NotEquals:
        return QLatin1String(" != ");
    case Less:
        return QLatin1String(" < ");
    case LessOrEqual:
        return QLatin1String(" <= ");
    case Greater:
        return QLatin1String(" > ");
    case GreaterOrEqual:
        return QLatin1String(" >= ");
    case In:
        return QLatin1String(" in ");
    case Has:
        return QLatin1String(" has ");
    }

    Q_ASSERT(false);
    return QString();
}

QString FileSearchQuery::Private::logicOperatorToString(FileSearchQuery::LogicOperator op)
{
    switch (op) {
    case And:
        return QLatin1String(" and ");
    case Or:
        return QLatin1String(" or ");
    }

    Q_ASSERT(false);
    return QString();
}

QString FileSearchQuery::Private::valueToString(FileSearchQuery::Field field, const QVariant &var)
{
    switch (field) {
    case Title:
    case FullText:
    case MimeType:
    case Parents:
    case Owners:
    case Writers:
    case Readers:
        return QString::fromLatin1("'%1'").arg(var.toString().replace(QLatin1Char('\''), QLatin1String("\\\'")));
    case ModifiedDate:
    case LastViewedByMeDate:
        return QString::fromLatin1("'%1'").arg(var.toDateTime().toUTC().toString(QLatin1String("yyyy-MM-ddThh:mm:ss")));
    case Trashed:
    case Starred:
    case SharedWithMe:
        return (var.toBool() == true ? QLatin1String("true") : QLatin1String("false"));
    }

    Q_ASSERT(false);
    return QString();
}

FileSearchQuery::FileSearchQuery(FileSearchQuery::LogicOperator op)
    : d(new Private)
{
    d->logicOp = op;
}

FileSearchQuery::FileSearchQuery(const FileSearchQuery &other)
    : d(other.d)
{
}

FileSearchQuery::~FileSearchQuery()
{
}

FileSearchQuery &FileSearchQuery::operator=(const FileSearchQuery &other)
{
    d = other.d;
    return *this;
}


void FileSearchQuery::addQuery(FileSearchQuery::Field field, FileSearchQuery::CompareOperator op, const QVariant &value)
{
    switch (field) {
    case Title:
    case MimeType:
        Q_ASSERT(op == Contains || op == Equals || op == NotEquals);
        Q_ASSERT(value.canConvert<QString>());
        break;
    case FullText:
        Q_ASSERT(op == Contains);
        Q_ASSERT(value.canConvert<QString>());
        break;
    case ModifiedDate:
    case LastViewedByMeDate:
        Q_ASSERT(op == LessOrEqual || op == Less || op == Equals || op == NotEquals || op == Greater || op == GreaterOrEqual);
        Q_ASSERT(value.canConvert<QDateTime>());
        break;
    case Trashed:
    case Starred:
    case SharedWithMe:
        Q_ASSERT(op == Equals || op == NotEquals);
        Q_ASSERT(value.canConvert<bool>());
        break;
    case Parents:
    case Owners:
    case Writers:
    case Readers:
        Q_ASSERT(op == In);
        Q_ASSERT(value.canConvert<QString>());
        break;
    }

    FileSearchQuery query;
    query.d->field = field;
    query.d->compareOp = op;
    query.d->value = value;
    d->subqueries.append(query);
}

void FileSearchQuery::addQuery(const FileSearchQuery &query)
{
    d->subqueries.append(query);
}

bool FileSearchQuery::isEmpty() const
{
    return d->value.isNull() && d->subqueries.isEmpty();
}

QString FileSearchQuery::serialize() const
{
    if (isEmpty()) {
        return QString();
    }

    QString r;
    r = QLatin1Char('(');
    if (d->subqueries.isEmpty()) {
        if (d->compareOp == In) {
            r += QString::fromLatin1("%1 in %2").arg(Private::valueToString(d->field, d->value),
                                                     Private::fieldToString(d->field));
        } else {
            r += Private::fieldToString(d->field) % Private::compareOperatorToString(d->compareOp) % Private::valueToString(d->field, d->value);
        }
    } else {
        QList<FileSearchQuery>::ConstIterator iter, end;
        for (iter = d->subqueries.constBegin(), end = d->subqueries.constEnd(); iter != end; ++iter) {
            if (iter != d->subqueries.constBegin()) {
                r += Private::logicOperatorToString(d->logicOp);
            }
            r += (*iter).serialize();
        }
    }
    r += QLatin1Char(')');

    return r;
}


