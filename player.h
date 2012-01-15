#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player
{
public:
    Player(std::string name="player");

private:
    std::string name;
    int x, y, z;
};

#endif // PLAYER_H
