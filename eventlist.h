#ifndef EVENTLIST_H
#define EVENTLIST_H

#include <QList>
#include <QPair>
#include <QVariant>

enum BEvent{

    //List Management
    NONE_EVENT, //No event on the list

    //Object management
    CREATE,
    UPDATE_ORIENTATION,
    UPDATE_POSITION,
    UPDATE_SCALE,
    UPDATE_COLOR,
    ATTACH,
    DETACH,
    DELETE,

    //Match management
    START_DM,
    START_CTF,
    START_TDM,
    ENDING_MATCH,

    //HUD management
    SET_PLAYER_SCORE,//kills and deaths
    SET_TEAM_SCORE // in TDM,CTF
};


class EventList
{
public:
    EventList();
    void push(QPair<BEvent, QList<QVariant> >);
    QPair<BEvent, QList<QVariant> > pop();

private:
    QList<QPair<BEvent, QList<QVariant > > > events;
};

#endif // EVENTLIST_H
