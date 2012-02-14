#ifndef BULLET_H
#define BULLET_H

#include "actor.h"

class Bullet : public Actor
{
public:
    Bullet(QString name = "");
    Bullet(QVariantMap map);

    int getId();

    QString player;
    int id;
};

#endif // BULLET_H
