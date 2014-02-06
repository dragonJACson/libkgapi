/*
 * This file is part of LibKGAPI library
 *
 * Copyright (C) 2013  Daniel Vrátil <dvratil@redhat.com>
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

#ifndef KGAPI2_DRIVEPERMISSIONCREATEJOB_H
#define KGAPI2_DRIVEPERMISSIONCREATEJOB_H

#include <libkgapi2/createjob.h>
#include <libkgapi2/libkgapi2_export.h>

namespace KGAPI2
{

namespace Drive
{

class LIBKGAPI2_EXPORT PermissionCreateJob : public KGAPI2::CreateJob
{
    Q_OBJECT

  public:
    explicit PermissionCreateJob(const QString &fileId,
                                 const PermissionPtr &permission,
                                 const AccountPtr &account, QObject *parent = 0);
    explicit PermissionCreateJob(const QString &fileId,
                                 const PermissionsList &permissions,
                                 const AccountPtr &account, QObject *parent = 0);
    virtual ~PermissionCreateJob();

  protected:
    virtual void start();
    virtual KGAPI2::ObjectsList handleReplyWithItems(const QNetworkReply *reply,
                                                     const QByteArray &rawData);

  private:
    class Private;
    Private *const d;
    friend class Private;
};

} // namespace Drive

} // namespace KGAPI2

#endif // KGAPI2_DRIVEPERMISSIONCREATEJOB_H
