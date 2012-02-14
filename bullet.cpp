#include "bullet.h"

Bullet::Bullet(QVariantMap map)
    : Actor(map)
{
    player = map["player"].toString();
    id = map["id"].toInt();
}

int Bullet::getId()
{
    return id;
}
