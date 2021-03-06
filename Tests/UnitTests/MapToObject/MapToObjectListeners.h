/****************************************************************************
**
** Copyright (C) VCreate Logic Private Limited, Bangalore
**
** Use of this file is limited according to the terms specified by
** VCreate Logic Private Limited, Bangalore.  Details of those terms
** are listed in licence.txt included as part of the distribution package
** of this file. This file may not be distributed without including the
** licence.txt file.
**
** Contact info@vcreatelogic.com if any conditions of this licensing are
** not clear to you.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/

#ifndef MAPTOOBJECTLISTENERS_H
#define MAPTOOBJECTLISTENERS_H

#include <GCF3/MapToObject>

struct SimpleListenerEvent
{
    SimpleListenerEvent() : Object(0), Event(-1), Value(-1) { }
    SimpleListenerEvent(QObject *o, int e, int v)
        : Object(o), Event(e), Value(v) { }

    QObject *Object;
    int Event;
    int Value;
};

class SimpleListener : public GCF::MapToObjectEventListener
{
    QList<SimpleListenerEvent> m_events;
    GCF::MapToObject<int>* m_map;

public:
    SimpleListener() : m_map(0) { }

    enum Event
    {
        UnknownEvent = -1,
        InsertObjectEvent,
        RemoveObjectEvent,
        DeleteObjectEvent
    };

    void setMap(GCF::MapToObject<int>& map) { m_map = &map; }
    GCF::MapToObject<int>& map() const { return *m_map; }

    const QList<SimpleListenerEvent>& events() const { return m_events; }

    QObject *lastObjectPointer() const { return m_events.last().Object; }
    Event lastEvent() const { return Event( m_events.last().Event ); }
    int lastEventValue() const { return m_events.last().Value; }
    void reset() { m_events.clear(); }

    virtual QString listenerType() const { return "SimpleListener"; }
    virtual void objectInserted(QObject *object) {
        int v = m_map ? m_map->map().key(object, -1) : -1;
        m_events.append( SimpleListenerEvent(object, InsertObjectEvent, v) );
    }
    virtual void objectRemoved(QObject *object) {
        int v = m_map ? m_map->map().key(object, -1) : -1;
        m_events.append( SimpleListenerEvent(object, RemoveObjectEvent, v) );
    }
    virtual void objectDeleted(QObject *object) {
        int v = m_map ? m_map->map().key(object, -2) : -2;
        m_events.append( SimpleListenerEvent(object, DeleteObjectEvent, v) );
    }
};

#endif // MAPTOOBJECTLISTENERS_H
