#include <qjson/parser.h>
#include <QVariant>
#include <QDebug>
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
    QList<Player> ret(players);
    players.clear();

    return ret;
}

void Model::setUpdatedPlayers(QList<Player> p)
{
    players = p;
}

void Model::setUpdatedPlayers(QString json)
{
    QJson::Parser parser;
    QVariantMap result = parser.parse(json.toAscii()).toMap();

    foreach(QVariant obj, result["players"].toList()){
        QVariantMap map = obj.toMap();
        qDebug() << map;
        Player p(map["name"].toString(), map["x"].toInt(), map["y"].toInt(), map["z"].toInt());
        addUpdatedPlayer(p);
    }
}

void Model::addUpdatedPlayer(Player p)
{
    QMutexLocker locker(&mutex);
    players.append(p);
}

void Model::updateKeys(QString name, bool state)
{
    emit keyChanged(name, state);
    qDebug() << "Emited keys signal";
}
