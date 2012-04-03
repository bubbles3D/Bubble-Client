#ifndef ACTOR_H
#define ACTOR_H

#include <QString>
#include <QVariant>

class Actor
{
public:
    Actor();
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
    float getWidth();
    float getLength();
    float getHeight();
    int getCube();
    void update(QVariantMap map);

    QString id;
    float x, y, z;
    float vx, vy, vz;
    float ratio;
    float width, length, height;
    int cube;

    bool operator ==(const Actor& a) const;
};

#endif // ACTOR_H
