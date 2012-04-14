#include <QDebug>
#include "player.h"

Player::Player()
{
    //TODO
}

Player::Player(QVariantMap map)
    :Actor(map)
{
    name = map["name"].toString();
    life = map["life"].toInt();
    deaths = map["deaths"].toInt();
    kills = map["kills"].toInt();
}

void Player::update(QVariantMap map)
{
    Actor::update(map);

    if (map.contains("name"))
        name = map["name"].toString();
    if (map.contains("life"))
        life = map["life"].toInt();
    if (map.contains("deaths"))
        deaths = map["deaths"].toInt();
    if (map.contains("kills"))
        kills = map["kills"].toInt();
    if (map.contains("flag"))
        flag = map["flag"];
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


QString Player::getName()
{
    return name;
}
