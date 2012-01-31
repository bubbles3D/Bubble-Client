#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <QString>
#include <QVariant>

class Player
{
public:
    Player(QString name="player", float x=0, float y=0, float z=0,
           float vx=0, float vy=0, float vz=0);
    Player(QVariantMap dict);
    QString toString();
    float getX();
    float getY();
    float getZ();
    float getVx();
    float getVy();
    float getVz();
    QString getName();

private:
    QString name;
    float x, y, z;
    float vx, vy, vz;
};

#endif // PLAYER_H
