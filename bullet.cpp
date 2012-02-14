#include "bullet.h"

Bullet::Bullet(QVariantMap map)
    : Actor(map)
{
    player = map["player"].toString();
    id = map["id"].toInt();
    name = map["id"].toString();
}

int Bullet::getId()
{
    return id;
}
