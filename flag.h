#ifndef FLAG_H
#define FLAG_H

#include "actor.h"

class Flag: public Actor
{
public:
    Flag();
    Flag(QVariantMap map);

    void update(QVariantMap map);

    int team;
};

#endif // FLAG_H
