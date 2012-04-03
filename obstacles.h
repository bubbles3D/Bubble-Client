#ifndef OBSTACLES_H
#define OBSTACLES_H

#include <QVariantMap>
#include "actor.h"

class Obstacles : public Actor
{
public:
    Obstacles();
    Obstacles(QVariantMap data);
};

#endif // OBSTACLES_H
