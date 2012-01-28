#ifndef MODEL_H
#define MODEL_H

#include <QList>
#include <QMutex>

#include "player.h"

class Model
{
public:
    static Model * getInstance();
    void setUpdatedPlayers(QList<Player> p);
    void setUpdatedPlayers(QString json);
    QList<Player> getUpdatedPlayers();

private:
    static Model * instance;
    Model();
    QList<Player> players;
    QMutex mutex;

};

#endif // MODEL_H
