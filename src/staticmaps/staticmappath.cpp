/*
    Copyright (C) 2012  Jan Grulich <grulja@gmail.com>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) version 3, or any
    later version accepted by the membership of KDE e.V. (or its
    successor approved by the membership of KDE e.V.), which shall
    act as a proxy defined in Section 6 of version 3 of the license.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "staticmappath.h"

using namespace KGAPI2;


class Q_DECL_HIDDEN StaticMapPath::Private
{
  public:
    Private();
    Private(const Private &other);

    void init(const Private &other);

    StaticMapPath::LocationType locationType;

    QColor color;
    QColor fillColor;
    quint8 weight;

    QStringList locationsString;
    KContacts::Address::List locationsAddress;
    QList<KContacts::Geo> locationsGeo;
};


StaticMapPath::Private::Private():
    color(Qt::blue),
    weight(5)
{
}

StaticMapPath::Private::Private(const Private & other)
{
    init(other);
}

void StaticMapPath::Private::init(const Private &other)
{
    locationType = other.locationType;
    color = other.color;
    fillColor = other.fillColor;
    weight = other.weight;
    locationsString = other.locationsString;
    locationsAddress = other.locationsAddress;
    locationsGeo = other.locationsGeo;
}

StaticMapPath::StaticMapPath():
    d(new Private)
{
}

StaticMapPath::StaticMapPath(const StaticMapPath& other):
    d(new Private(*(other.d)))
{
}

StaticMapPath::StaticMapPath(const QStringList & locations, const quint8 weight,
                             const QColor & color, const QColor & fillColor):
    d(new Private)
{
    d->locationType = String;
    d->locationsString = locations;
    d->weight = weight;
    d->color = color;
    d->fillColor = fillColor;
}

StaticMapPath::StaticMapPath(const KContacts::Address::List& locations, const quint8 weight,
                             const QColor & color, const QColor & fillColor):
    d(new Private)
{
    d->locationType = KABCAddress;
    d->locationsAddress = locations;
    d->weight = weight;
    d->color = color;
    d->fillColor = fillColor;
}

StaticMapPath::StaticMapPath(const QList< KContacts::Geo >& locations, const quint8 weight,
                             const QColor & color, const QColor & fillColor):
    d(new Private)
{
    d->locationType = KABCGeo;
    d->locationsGeo = locations;
    d->weight = weight;
    d->color = color;
    d->fillColor = fillColor;
}

StaticMapPath::~StaticMapPath()
{
    delete d;
}

StaticMapPath::LocationType StaticMapPath::locationType() const
{
    return d->locationType;
}

QColor StaticMapPath::color() const
{
    return d->color;
}

void StaticMapPath::setColor(const QColor & color)
{
    d->color = color;
}

bool StaticMapPath::isValid() const
{
    return (d->locationType != Undefined);
}

QColor StaticMapPath::fillColor() const
{
    return d->fillColor;
}

void StaticMapPath::setFillColor(const QColor & color)
{
    d->fillColor = color;
}

QStringList StaticMapPath::locationsString() const
{
    return d->locationsString;
}

void StaticMapPath::setLocations(const QStringList & locations)
{
    d->locationType = String;
    d->locationsString = locations;
    d->locationsAddress.clear();
    d->locationsGeo.clear();
}

KContacts::Address::List StaticMapPath::locationsAddress() const
{
    return d->locationsAddress;
}

void StaticMapPath::setLocations(const KContacts::Address::List &locations)
{
    d->locationType = KABCAddress;
    d->locationsAddress = locations;
    d->locationsString.clear();
    d->locationsGeo.clear();
}

QList< KContacts::Geo > StaticMapPath::locationsGeo() const
{
    return d->locationsGeo;
}

void StaticMapPath::setLocations(const QList< KContacts::Geo >& locations)
{
    d->locationType = KABCGeo;
    d->locationsGeo = locations;
    d->locationsString.clear();
    d->locationsAddress.clear();
}

QString StaticMapPath::toString() const
{
    QString ret;

    if (d->color != Qt::blue)
        ret += QLatin1String("color:") + d->color.name().replace(QLatin1Char('#'), QLatin1String("0x")) + QLatin1String("|");
    if (d->weight != 5)
        ret += QLatin1String("weight:") + QString::number(d->weight) + QLatin1String("|");
    if (d->fillColor.isValid())
        ret += QLatin1String("fillcolor:") + d->fillColor.name().replace(QLatin1Char('#'), QLatin1String("0x")) + QLatin1String("|");

    if (locationType() == String) {

        for (const QString & addr : qAsConst(d->locationsString)) {
            ret += addr + QLatin1String("|");
        }

    } else if (locationType() == KABCAddress) {

        for (const KContacts::Address & addr : qAsConst(d->locationsAddress)) {
            ret += addr.formattedAddress() + QLatin1String("|");
        }

    } else if (locationType() == KABCGeo) {

        for (const KContacts::Geo & addr : qAsConst(d->locationsGeo)) {
            ret += QString::number(addr.latitude()) + QLatin1String(",") +
                  QString::number(addr.longitude()) + QLatin1String("|");
        }

    }

    ret = ret.replace(QLatin1String(", "), QLatin1String(","));
    ret = ret.replace(QLatin1String(". "), QLatin1String("."));
    ret = ret.replace(QLatin1Char(' '), QLatin1Char('+'));
    ret = ret.replace(QLatin1Char('\n'), QLatin1Char(','));
    ret = ret.remove(ret.lastIndexOf(QLatin1Char('|')), 1);

    return ret;
}

quint8 StaticMapPath::weight() const
{
    return d->weight;
}

void StaticMapPath::setWeight(const quint8 weight)
{
    d->weight = weight;
}

StaticMapPath& StaticMapPath::operator=(const StaticMapPath& other)
{
    if (&other == this) {
        return *this;
    }

    d->init(*(other.d));
    return *this;
}

