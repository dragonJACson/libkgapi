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

#include "filedeletejob.h"
#include "account.h"
#include "driveservice.h"
#include "file.h"

#include <QNetworkRequest>

using namespace KGAPI2;
using namespace KGAPI2::Drive;

class Q_DECL_HIDDEN FileDeleteJob::Private
{
  public:
    QStringList filesIDs;
};

FileDeleteJob::FileDeleteJob(const QString &fileId,
                             const AccountPtr &account,
                             QObject *parent):
    DeleteJob(account, parent),
    d(new Private)
{
    d->filesIDs << fileId;
}

FileDeleteJob::FileDeleteJob(const QStringList &filesIds,
                             const AccountPtr &account,
                             QObject *parent):
    DeleteJob(account, parent),
    d(new Private)
{
    d->filesIDs << filesIds;
}

FileDeleteJob::FileDeleteJob(const FilePtr &file,
                             const AccountPtr &account,
                             QObject *parent):
    DeleteJob(account, parent),
    d(new Private)
{
    d->filesIDs << file->id();
}

FileDeleteJob::FileDeleteJob(const FilesList &files,
                             const AccountPtr &account,
                             QObject *parent):
    DeleteJob(account, parent),
    d(new Private)
{
    for (const FilePtr & file : qAsConst(files)) {
        d->filesIDs << file->id();
    }
}

FileDeleteJob::~FileDeleteJob()
{
    delete d;
}

void FileDeleteJob::start()
{
    if (d->filesIDs.isEmpty()) {
        emitFinished();
        return;
    }

    const QString fileId = d->filesIDs.takeFirst();
    const QUrl url = DriveService::deleteFileUrl(fileId);

    QNetworkRequest request(url);
    request.setRawHeader("Authorization", "Bearer " + account()->accessToken().toLatin1());

    enqueueRequest(request);
}


