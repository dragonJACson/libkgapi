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

#ifndef KGAPI2_ONEDRIVEAPPFETCHJOB_H
#define KGAPI2_ONEDRIVEAPPFETCHJOB_H

#include "fetchjob.h"
#include "kgapionedrive_export.h"

namespace KGAPI2
{

namespace OneDrive
{

class KGAPIONEDRIVE_EXPORT AppFetchJob : public KGAPI2::FetchJob
{
    Q_OBJECT
  public:
    explicit AppFetchJob(const AccountPtr &account, QObject *parent = nullptr);
    explicit AppFetchJob(const QString &appId, const AccountPtr &account,
                         QObject *parent = nullptr);
    ~AppFetchJob() override;

  protected:
    void start() override;
    KGAPI2::ObjectsList handleReplyWithItems(const QNetworkReply *reply,
                                                     const QByteArray &rawData) override;

  private:
    class Private;
    Private *const d;
    friend class Private;
};

} // namespace OneDrive

} // namespace KGAPI2

#endif // KGAPI2_ONEDRIVEAPPFETCHJOB_H
