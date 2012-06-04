/*
    Copyright 2012  Dan Vratil <dan@progdan.cz>

    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License as
    published by the Free Software Foundation; either version 2 of
    the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef LIBKGAPI_OBJECTS_CALENDAR_P_H
#define LIBKGAPI_OBJECTS_CALENDAR_P_H

#include <QtCore/QSharedData>
#include <QtCore/QString>

#ifdef WITH_KCAL
#include <KCal/Alarm>
using namespace KCal;
#else
#include <KCalCore/Alarm>
using namespace KCalCore;
#endif

namespace KGAPI
{

namespace Objects
{

class ReminderData: public QSharedData
{
  public:
    ReminderData();
    ReminderData(const ReminderData &other);
    ~ReminderData() {};

    Alarm::Type type;
    Duration offset;
};

class CalendarData: public QSharedData
{
  public:
    CalendarData() {};
    CalendarData(const CalendarData &other);
    ~CalendarData() {};

    QString uid;
    QString title;
    QString details;
    QString timezone;
    QString location;
    bool editable;

    Reminder::List reminders;
};

} // namespace Objects

} // namespace KGAPI

#endif /* LIBKGAPI_OBJECTS_CALENDAR_P_H */