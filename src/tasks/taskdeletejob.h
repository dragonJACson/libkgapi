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


#ifndef LIBKGAPI2_TASKDELETEJOB_H
#define LIBKGAPI2_TASKDELETEJOB_H

#include "deletejob.h"
#include "kgapitasks_export.h"

namespace KGAPI2 {

/**
 * @brief A job to delete one or more tasks from tasklist in
 *        user's Google Tasks account
 *
 * Note that operation is irreversible.
 *
 * @author Daniel Vrátil <dvratil@redhat.com>
 * @since 2.0
 */
class KGAPITASKS_EXPORT TaskDeleteJob : public KGAPI2::DeleteJob
{
    Q_OBJECT

  public:

    /**
     * @brief Constructs a new job that will delete given @p task from a
     *        tasklist with given @p taskListId
     *
     * @param task Task to delete
     * @param taskListId ID of tasklist in which the task is stored
     * @param account Account to authenticate the request
     * @param parent
     */
    explicit TaskDeleteJob(const TaskPtr &task, const QString &taskListId,
                           const AccountPtr &account, QObject* parent = nullptr);

    /**
     * @brief Constructs a new job that will delete given @p tasks from a
     *        tasklist with given @p taskListId
     *
     * @param tasks Tasks to delete
     * @param taskListId ID of tasklist in which the task is stored
     * @param account Account to authenticate the request
     * @param parent
     */
    explicit TaskDeleteJob(const TasksList &tasks, const QString &tasklistId,
                           const AccountPtr &account, QObject* parent = nullptr);

    /**
     * @brief Constructs a new job that will delete task with given @p taskId
     *        from a tasklist with given @p taskListId
     *
     * @param taskId ID of task to delete
     * @param taskListId ID of tasklist in which the task is stored
     * @param account Account to authenticate the request
     * @param parent
     */
    explicit TaskDeleteJob(const QString &taskId, const QString &taskListId,
                           const AccountPtr &account, QObject* parent = nullptr);

    /**
     * @brief Constructs a new job that will delete tasks with given @p tasksIds
     *        from a tasklist with given @p taskListId
     *
     * @param tasksIds IDs of tasks to delete
     * @param taskListId ID of tasklist in which the task is stored
     * @param account Account to authenticate the request
     * @param parent
     */
    explicit TaskDeleteJob(const QStringList &tasksIds, const QString &taskListId,
                           const AccountPtr &account, QObject *parent = nullptr);

    /**
     * @brief Destructor
     */
    ~TaskDeleteJob() override;

  protected:

    /**
     * @brief KGAPI2::Job::start implementation
     */
    void start() override;

    /**
     * @brief KGAPI2::Job::handleReply implementation
     *
     * @param reply
     * @param rawData
     */
    void handleReply(const QNetworkReply* reply, const QByteArray& rawData) override;

  private:
    class Private;
    Private * const d;
    friend class Private;
};

} // namespace KGAPI2

#endif // LIBKGAPI2_TASKDELETEJOB_H
