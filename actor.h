#ifndef ACTOR_H
#define ACTOR_H

#include <QString>
#include <QVariant>

class Actor
{
public:
    Actor(QString name="player", float x=0, float y=0, float z=0,
           float vx=0, float vy=0, float vz=0);
    Actor(QVariantMap dict);
    QString toString();
    float getX();
    float getY();
    float getZ();
    float getVx();
    float getVy();
    float getVz();
    QString getName();
    float getRatio();

private:
    QString name;
    float x, y, z;
    float vx, vy, vz;
    float ratio;
};

#endif // ACTOR_H
