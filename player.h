#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <QString>
#include <QVariant>

#include "actor.h"

class Player: public Actor
{
public:
    Player();
    Player(QString id, float x, float y, float z,
                   float vx, float vy, float vz);
    Player(QVariantMap map);

    int getLife();
    int getDeaths();
    int getKills();
    QString getName();
    void update(QVariantMap map);

    int life, deaths, kills;
    bool flag;
    QString name;

};

#endif // PLAYER_H
