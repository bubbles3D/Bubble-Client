#include "player.h"




Player::Player(QString name, float x, float y, float z,
               float vx, float vy, float vz)
    : Actor(name, x, y, z, vx, vy, vz)
{}

Player::Player(QVariantMap map)
    :Actor(map)
{}
