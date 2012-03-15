#include "actor.h"

Actor::Actor(QString id, float x, float y, float z,
               float vx, float vy, float vz)
{
    this->id = id;
    this->x = x;
    this->y = y;
    this->z = z;
    this->vx = vx;
    this->vy = vy;
    this->vz = vz;
}

Actor::Actor(QVariantMap map)
{
    id = map["id"].toString();
    x = map["x"].toInt();
    y = map["y"].toInt();
    z = map["z"].toInt();
    vx = map["vx"].toInt();
    vy = map["vy"].toInt();
    vz = map["vz"].toInt();
    width = map["w"].toFloat();
    height = map["h"].toFloat();
    length = map["l"].toFloat();
    cube = map["cube"].toInt();
}

QString Actor::toString()
{
    QString str = "name : " + id + " x:" + x + " y:" + y + " z:" + z;

    return str;
}

QString Actor::getId(){
    return id;
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

float Actor::getWidth(){
    return width;
}

float Actor::getLength(){
    return length;
}

float Actor::getHeight(){
    return height;
}

bool Actor::operator ==(const Actor& a) const{
    return (id == a.id);
}

int Actor::getCube()
{
    return cube;
}

