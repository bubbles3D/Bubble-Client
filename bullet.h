#ifndef BULLET_H
#define BULLET_H

#include "actor.h"

class Bullet : public Actor
{
public:
    Bullet(QString name = "");
    Bullet(QVariantMap map);

private:
    QString player;
};

#endif // BULLET_H
