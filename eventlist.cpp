#include "eventlist.h"

EventList::EventList()
{
}

void EventList::push(QPair<BEvent, QList<QVariant> > event)
{
    events.append(event);
}


QPair<BEvent, QList<QVariant> > EventList::pop()
{
    if (events.isEmpty()) {
        return QPair<BEvent, QList<QVariant> >(NONE_EVENT, QList<QVariant>());
    }

    return events.takeFirst();
}
