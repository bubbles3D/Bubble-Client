#include "player.h"


Player::Player(QString name, float x, float y, float z)
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

QString Player::getName(){
    return name;
}

float Player::getX(){
    return x;
}

float Player::getY(){
    return y;
}

float Player::getZ(){
    return z;
}
