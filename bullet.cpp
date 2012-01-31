#include "bullet.h"

Bullet::Bullet(QVariantMap map)
    : Actor(map)
{
    player = map["player"].toString();
}
