#include "bullet.h"

Bullet::Bullet()
{
    //TODO
}

Bullet::Bullet(QVariantMap map)
    : Actor(map)
{
    player = map["player"].toString();
    id = map["id"].toInt();
    id = map["id"].toString();
}

void Bullet::update(QVariantMap map)
{
    Actor::update(map);
}
