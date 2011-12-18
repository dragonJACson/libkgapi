/*
    libKGoogle - Objects - Event
    Copyright (C) 2011  Dan Vratil <dan@progdan.cz>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#include "event.h"
#include "event_p.h"

#include <qvariant.h>
#include <qstring.h>
#include <qdebug.h>

using namespace KGoogle;

#ifdef WITH_KCAL
using namespace KCal;
#else
using namespace KCalCore;
#endif

Objects::EventData::EventData(const Objects::EventData &other):
    QSharedData(other),
    deleted(other.deleted),
    id(other.id),
    etag(other.etag)
{ }


Objects::Event::Event()
{
    d = new EventData;
}

Objects::Event::Event(const Objects::Event &other):
  KGoogle::Object(other),
#ifdef WITH_KCAL
  KCal::Event(other),
#else
  KCalCore::Event(other),
#endif
  d(other.d)
{ }

#ifdef WITH_KCAL
Objects::Event::Event(const KCal::Event &event): 
  KCal::Event(event),
#else
Objects::Event::Event(const KCalCore::Event &event):
  KCalCore::Event(event),
#endif
  d(new EventData)
{ }


Objects::Event::~Event()
{ }

void Objects::Event::setDeleted(const bool deleted)
{
  d->deleted = deleted;
}

bool Objects::Event::deleted()
{
  return d->deleted;
}

void Objects::Event::setId(const QString& id)
{
  setUid(id);
}

QString Objects::Event::id()
{
  return uid();
}



Objects::Event& Objects::Event::operator=( const Objects::Event& other )
{
  d = other.d;
  return *this;
}
