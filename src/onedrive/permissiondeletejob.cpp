/*
 * This file is part of LibKGAPI library
 *
 * Copyright (C) 2013  Daniel Vrátil <dvratil@redhat.com>
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


#include "permissiondeletejob.h"
#include "permission.h"
#include "account.h"
#include "onedriveservice.h"

#include <QNetworkRequest>

using namespace KGAPI2;
using namespace KGAPI2::OneDrive;

class Q_DECL_HIDDEN PermissionDeleteJob::Private
{
  public:
    QString fileId;
    QStringList permissionsIds;
};

PermissionDeleteJob::PermissionDeleteJob(const QString &fileId,
                                         const PermissionPtr &permission,
                                         const AccountPtr &account,
                                         QObject *parent):
    DeleteJob(account, parent),
    d(new Private)
{
    d->fileId = fileId;
    d->permissionsIds << permission->id();
}

PermissionDeleteJob::PermissionDeleteJob(const QString &fileId,
                                         const QString &permissionId,
                                         const AccountPtr &account,
                                         QObject *parent):
    DeleteJob(account, parent),
    d(new Private)
{
    d->fileId = fileId;
    d->permissionsIds << permissionId;
}

PermissionDeleteJob::PermissionDeleteJob(const QString &fileId,
                                         const PermissionsList &permissions,
                                         const AccountPtr &account,
                                         QObject *parent):
    DeleteJob(account, parent),
    d(new Private)
{
    d->fileId = fileId;
    for (const PermissionPtr & permission : qAsConst(permissions)) {
        d->permissionsIds << permission->id();
    }
}

PermissionDeleteJob::PermissionDeleteJob(const QString &fileId,
                                         const QStringList &permissionsIds,
                                         const AccountPtr &account,
                                         QObject *parent):
    DeleteJob(account, parent),
    d(new Private)
{
    d->fileId = fileId;
    d->permissionsIds << permissionsIds;
}

PermissionDeleteJob::~PermissionDeleteJob()
{
    delete d;
}

void PermissionDeleteJob::start()
{
    if (d->permissionsIds.isEmpty()) {
        emitFinished();
        return;
    }

    const QString permissionId = d->permissionsIds.takeFirst();
    const QUrl url = OneDriveService::deletePermissionUrl(d->fileId, permissionId);
    QNetworkRequest request(url);
    request.setRawHeader("Authorization", "Bearer " + account()->accessToken().toLatin1());

    enqueueRequest(request);
}


