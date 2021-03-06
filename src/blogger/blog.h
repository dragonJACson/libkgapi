/*
 * Copyright (C) 2014  Daniel Vrátil <dvratil@redhat.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) version 3, or any
 * later version accepted by the membership of KDE e.V. (or its
 * successor approved by the membership of KDE e.V.), which shall
 * act as a proxy defined in Section 6 of version 3 of the license.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef KGAPI2_BLOG_H
#define KGAPI2_BLOG_H

#include "object.h"
#include "kgapiblogger_export.h"

#include <QDateTime>
#include <QVariant>

namespace KGAPI2
{

namespace Blogger
{

class KGAPIBLOGGER_EXPORT Blog : public KGAPI2::Object
{
  public:
    explicit Blog();
    ~Blog();

    QString id() const;
    QString name() const;
    QString description() const;
    QDateTime published() const;
    QDateTime updated() const;
    QUrl url() const;
    uint postsCount() const;
    uint pagesCount() const;
    QString language() const;
    QString country() const;
    QString languageVariant() const;
    QVariant customMetaData() const;

    static BlogPtr fromJSON(const QByteArray &rawData);
    static BlogsList fromJSONFeed(const QByteArray &rawData);

  private:
    Q_DISABLE_COPY(Blog)

    class Private;
    Private * const d;
    friend class Private;
};

} // namespace Blogger
} // namespace KGAPI2

#endif // KGAPI2_BLOG_H
