#include <cstring>

#include "model.h"

Model* Model::instance = NULL;

Model::Model()
{

}

Model* Model::getInstance()
{
    if (Model::instance == NULL)
    {
        Model::instance = new Model();
    }

    return Model::instance;
}


QList<Player> Model::getUpdatedPlayers()
{
    QMutexLocker locker(&mutex);
    QList<Player> ret(&players);
    players.clear();

    return ret;
}

void Model::setUpdatedPlayers(QList<Player> p)
{
    //TODO
}
