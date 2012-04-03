#ifndef BULLET_H
#define BULLET_H

#include "actor.h"

class Bullet : public Actor
{
public:
    Bullet();
    Bullet(QVariantMap map);
    void update(QVariantMap map);

    QString player;
};

#endif // BULLET_H
