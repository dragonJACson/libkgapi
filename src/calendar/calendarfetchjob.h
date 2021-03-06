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

#ifndef LIBKGAPI2_CALENDARFETCHJOB_H
#define LIBKGAPI2_CALENDARFETCHJOB_H

#include "fetchjob.h"
#include "kgapicalendar_export.h"

namespace KGAPI2 {

/**
 * @brief A job to fetch calendars from user's Google Calendar account.
 *
 * @author Daniel Vrátil <dvratil@redhat.com>
 * @since 2.0
 */
class KGAPICALENDAR_EXPORT CalendarFetchJob : public KGAPI2::FetchJob
{
    Q_OBJECT

  public:

    /**
     * @brief Constructs a job that will fetch all calendars from user's
     *        Google Calendar account
     *
     * @param account Account to authenticate the request
     * @param parent
     */
    explicit CalendarFetchJob(const AccountPtr &account, QObject* parent = nullptr);

    /**
     * @brief Constructs a job that will fetch a single calendar with given
     *        @p calendarId from user's Google Calendar account
     *
     * @param calendarId ID of calendar to fetch
     * @param account Account to authenticate the request
     * @param parent
     */
    explicit CalendarFetchJob(const QString &calendarId,
                              const AccountPtr &account, QObject* parent = nullptr);

    /**
     * @brief Destructor
     */
    ~CalendarFetchJob() override;

  protected:

    /**
     * @brief KGAPI2::Job::start implementation
     */
    void start() override;

    /**
     * @brief KGAPI2::FetchJob::handleReplyWithItems implementation
     *
     * @param reply
     * @param rawData
     */
    ObjectsList handleReplyWithItems(const QNetworkReply *reply,
                                             const QByteArray& rawData) override;

  private:
    class Private;
    Private * const d;
    friend class Private;

};

} // namespace KGAPI2

#endif // LIBKGAPI2_CALENDARFETCHJOB_H
