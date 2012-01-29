#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <QString>

class Player
{
public:
    Player(QString name="player", float x=0, float y=0, float z=0);
    QString toString();
    float getX();
    float getY();
    float getZ();
    QString getName();

private:
    QString name;
    float x, y, z;
};

#endif // PLAYER_H
