#include "actor.h"

Actor::Actor(QString name, float x, float y, float z,
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

Actor::Actor(QVariantMap map)
{
    name = map["name"].toString();
    x = map["x"].toInt();
    y = map["y"].toInt();
    z = map["z"].toInt();
    vx = map["vx"].toInt();
    vy = map["vy"].toInt();
    vz = map["vz"].toInt();
    ratio = map["ratio"].toInt();
}

QString Actor::toString()
{
    QString str;
    str += "name : " + name + " x:" + x + " y:" + y + " z:" + z;

    return str;
}

QString Actor::getName(){
    return name;
}

float Actor::getX(){
    return x;
}

float Actor::getY(){
    return y;
}

float Actor::getZ(){
    return z;
}

float Actor::getVx(){
    return vx;
}

float Actor::getVy(){
    return vy;
}

float Actor::getVz(){
    return vz;
}

float Actor::getRatio(){
    return ratio;
}

bool Actor::operator ==(const Actor& a) const{
    return (name == a.name);
}

