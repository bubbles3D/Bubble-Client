#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <QString>

class Player
{
public:
    Player(QString name="player", qint32 x=0, qint32 y=0, qint32 z=0);
    QString toString();

private:
    QString name;
    qint32 x, y, z;
};

#endif // PLAYER_H
