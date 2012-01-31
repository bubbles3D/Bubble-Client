#include "player.h"


Player::Player(QString name, float x, float y, float z,
               float vx, float vy, float vz)
{
    this->name = name;
    this->x = x;
    this->y = y;
    this->z = z;
    this->vx = vx;
    this->vy = vy;
    this->vz = vz;
}

Player::Player(QVariantMap map)
{
    name = map["name"].toString();
    x = map["x"].toInt();
    y = map["y"].toInt();
    z = map["z"].toInt();
    vx = map["vx"].toInt();
    vy = map["vy"].toInt();
    vz = map["vz"].toInt();
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

float Player::getVx(){
    return vx;
}

float Player::getVy(){
    return vy;
}

float Player::getVz(){
    return vz;
}

