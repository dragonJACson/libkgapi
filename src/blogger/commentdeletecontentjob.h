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

#ifndef KGAPI2_BLOGGER_COMMENTDELETECONTENTJOB_H
#define KGAPI2_BLOGGER_COMMENTDELETECONTENTJOB_H

#include "modifyjob.h"
#include "kgapiblogger_export.h"

namespace KGAPI2
{
namespace Blogger
{

class KGAPIBLOGGER_EXPORT CommentDeleteContentJob : public KGAPI2::ModifyJob
{
    Q_OBJECT

  public:
    explicit CommentDeleteContentJob(const QString &blogId,
                                     const QString &postId,
                                     const QString &commentId,
                                     const AccountPtr &account,
                                     QObject *parent = nullptr);
    explicit CommentDeleteContentJob(const CommentPtr &comment,
                                     const AccountPtr &account,
                                     QObject *parent = nullptr);
    ~CommentDeleteContentJob() override;

  protected:
    void start() override;
    ObjectsList handleReplyWithItems(const QNetworkReply *reply, const QByteArray &rawData) override;

  private:
    class Private;
    Private * const d;
    friend class Private;
};
}
}

#endif // KGAPI2_BLOGGER_COMMENTDELETECONTENTJOB_H
