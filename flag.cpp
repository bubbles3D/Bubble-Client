#include "flag.h"

Flag::Flag()
{
}

Flag::Flag(QVariantMap map)
    : Actor(map)
{
    team = map["team"].toInt();
}

void Flag::update(QVariantMap map)
{
    Actor::update(map);

    if (map.contains("team"))
        team = map["team"].toInt();
}
