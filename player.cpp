#include "player.h"



Player::Player(QVariantMap map)
    :Actor(map)
{
    name = map["name"].toString();
    life = map["life"].toInt();
    deaths = map["deaths"].toInt();
    kills = map["kills"].toInt();
    cube = map["cube"].toInt();
}

int Player::getLife()
{
    return life;
}

int Player::getKills()
{
    return kills;
}


int Player::getDeaths()
{
    return deaths;
}

int Player::getCube()
{
    return cube;
}

QString Player::getName()
{
    return name;
}
