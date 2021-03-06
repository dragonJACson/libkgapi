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

#ifndef KGAPI2_ONEDRIVEREVISIONDELETEJOB_H
#define KGAPI2_ONEDRIVEREVISIONDELETEJOB_H

#include "deletejob.h"
#include "kgapionedrive_export.h"

#include <QStringList>

namespace KGAPI2
{

namespace OneDrive
{

class KGAPIONEDRIVE_EXPORT RevisionDeleteJob : public KGAPI2::DeleteJob
{
    Q_OBJECT

  public:
    explicit RevisionDeleteJob(const QString &fileId, const QString &revisionId,
                               const AccountPtr &account, QObject *parent = nullptr);
    explicit RevisionDeleteJob(const QString &fileId, const QStringList &revisionsIds,
                               const AccountPtr &account, QObject *parent = nullptr);
    explicit RevisionDeleteJob(const QString &fileId, const RevisionPtr &revision,
                               const AccountPtr &account, QObject *parent = nullptr);
    explicit RevisionDeleteJob(const QString &fileId, const RevisionsList &revisions,
                               const AccountPtr &account, QObject *parent = nullptr);
    ~RevisionDeleteJob() override;

  protected:
    void start() override;

  private:
    class Private;
    Private *const d;
    friend class Private;
};

} // namespace OneDrive

} // namespace KGAPI2

#endif // KGAPI2_ONEDRIVEREVISIONDELETEJOB_H
