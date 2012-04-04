#include <QDebug>
#include "actor.h"

Actor::Actor()
{
    //TODO
}

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
    //Safegard 'cause default value changes ...
    x = y = z = vx = vy = vz = cube = 0;
    width = height = length = 0.0;

    id = map["id"].toString();
    x = map["x"].toInt();
    y = map["y"].toInt();
    z = map["z"].toInt();
    r = map["r"].toInt();
    g = map["g"].toInt();
    b = map["b"].toInt();
    vx = map["vx"].toFloat();
    vy = map["vy"].toFloat();
    vz = map["vz"].toFloat();
    width = map["w"].toFloat();
    height = map["h"].toFloat();
    length = map["l"].toFloat();
    cube = map["cube"].toInt();
}

void Actor::update(QVariantMap map)
{
    //Position
    if (map.contains("x"))
        x = map["x"].toInt();
    if (map.contains("y"))
        y = map["y"].toInt();
    if (map.contains("z"))
        z = map["z"].toInt();

    //Color
    if (map.contains("r"))
        r = map["r"].toInt();
    if (map.contains("g"))
        g = map["g"].toInt();
    if (map.contains("b"))
        b = map["b"].toInt();

    if (map.contains("vx"))
        vx = map["vx"].toFloat();
    if (map.contains("vy"))
        vy = map["vy"].toFloat();
    if (map.contains("vz"))
        vz = map["vz"].toFloat();
    if (map.contains("w"))
        width = map["w"].toFloat();
    if (map.contains("h"))
        height = map["h"].toFloat();
    if (map.contains("l"))
        length = map["l"].toFloat();
    if (map.contains("cube"))
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

void Actor::getColor(float* r, float* g, float* b)
{
    *r = this->r;
    *g = this->g;
    *b = this->b;
}
