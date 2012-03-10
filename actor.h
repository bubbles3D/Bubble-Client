#ifndef ACTOR_H
#define ACTOR_H

#include <QString>
#include <QVariant>

class Actor
{
public:
    Actor(QString id, float x, float y, float z,
                   float vx, float vy, float vz);
    Actor(QVariantMap dict);
    QString toString();
    float getX();
    float getY();
    float getZ();
    float getVx();
    float getVy();
    float getVz();
    QString getId();
    QString getName();
    float getRatio();

    QString id;
    float x, y, z;
    float vx, vy, vz;
    float ratio;

    bool operator ==(const Actor& a) const;
};

#endif // ACTOR_H
