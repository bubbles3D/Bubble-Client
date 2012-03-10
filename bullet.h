#ifndef BULLET_H
#define BULLET_H

#include "actor.h"

class Bullet : public Actor
{
public:
    Bullet(QVariantMap map);

    QString player;
};

#endif // BULLET_H
