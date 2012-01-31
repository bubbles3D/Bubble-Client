#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <QString>
#include <QVariant>

#include "actor.h"

class Player: public Actor
{
public:
    Player(QString name, float x, float y, float z,
                   float vx, float vy, float vz);
    Player(QVariantMap map);

};

#endif // PLAYER_H
