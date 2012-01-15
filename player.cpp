#include "player.h"


Player::Player(QString name, qint32 x, qint32 y, qint32 z)
{
    this->name = name;
    this->x = x;
    this->y = y;
    this->z = z;
}

QString Player::toString()
{
    QString str;
    str += "name : " + name + " x:" + x + " y:" + y + " z:" + z;

    return str;
}
