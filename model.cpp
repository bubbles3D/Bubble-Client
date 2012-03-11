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

    return players.values();
}

QList<Bullet> Model::getUpdatedBullets()
{
    QMutexLocker locker(&mutex);

    return bullets.values();
}

QList<Obstacles> Model::getUpdatedObstacles()
{
    QMutexLocker locker(&mutex);

    qDebug() << "get obstacles " << obstacles.size();
    return obstacles.values();
}


void Model::setUpdatedPlayers(QString json)
{
    //QMutexLocker locker(&mutex);
    QJson::Parser parser;
    QVariantMap result = parser.parse(json.toAscii()).toMap();
    QSet<QString> diff = players.keys().toSet();

    foreach(QVariant obj, result["players"].toList()){
        Player p(obj.toMap());
        addUpdatedPlayer(p);
        diff.remove(p.id);
    }

    foreach(QString s, diff){
        players.remove(s);
    }

    toClear.unite(diff);
}

void Model::setUpdatedBullets(QString json)
{
    //QMutexLocker locker(&mutex);
    QJson::Parser parser;
    QVariantMap result = parser.parse(json.toAscii()).toMap();
    QSet<QString> diff = bullets.keys().toSet();

    foreach(QVariant obj, result["bullets"].toList()){
        Bullet b(obj.toMap());
        addUpdatedBullet(b);
        diff.remove(b.id);
    }

    foreach(QString s, diff){
        bullets.remove(s);
    }

    toClear.unite(diff);
}

void Model::setUpdatedObstacles(QString json)
{
    //QMutexLocker locker(&mutex);
    QJson::Parser parser;
    QVariantMap result = parser.parse(json.toAscii()).toMap();
    QMap<QString, QVariant> field = result["field"].toMap();

    foreach(QVariant obj, field["obstacles"].toList()){
        Obstacles o(obj.toMap());
        addUpdatedObstacles(o);
    }
}

void Model::addUpdatedPlayer(Player p)
{
    QMutexLocker locker(&mutex);
    players.insert(p.id, p);
}

void Model::addUpdatedBullet(Bullet b)
{
    QMutexLocker locker(&mutex);
    bullets.insert(b.id, b);
}

void Model::addUpdatedObstacles(Obstacles o)
{
    QMutexLocker locker(&mutex);
    obstacles.insert(o.id, o);
}

void Model::setName(QString n)
{
    QMutexLocker locker(&mutex);
    name = n;
}

QString Model::getName()
{
    QMutexLocker locker(&mutex);
    return name;
}

void Model::updateKeys(QString name, bool state)
{
    emit keyChanged(name, state);
    qDebug() << "Emited keys signal";
}

void Model::updateMouse(float x, float y, float z)
{
    if(mouseTimeout.isNull())
    {
        mouseTimeout.start();
    }
    else if (mouseTimeout.elapsed() > 50)
    {
        emit mouseChanged(x, y, z);
        qDebug() << "Sent mouseEvent after " << mouseTimeout.elapsed();
        mouseTimeout.restart();
    }
}

void Model::shot(float x, float y, float z)
{
    emit shotEvent(x, y, z);
    qDebug() << "shotEvent sent";
}

/* Deprecated */
QList<Player> Model::getAllPlayers()
{
    QMutexLocker locker(&mutex);
    QList<Player> cp(players.values());
    return cp;
}

QList<QString> Model::getClearedActors(){
    QMutexLocker locker(&mutex);
    QList<QString> ret = toClear.toList();

    qDebug() << "getClearedActors " << ret;

    toClear.clear();

    return ret;
}

void Model::setMap(QString json)
{
    QMutexLocker locker(&mutex);
    QJson::Parser parser;
    QVariantMap result = parser.parse(json.toAscii()).toMap();
    QMap<QString, QVariant> field = result["field"].toMap();

    mapWidth = field["width"].toInt();
    mapLength = field["height"].toInt();
}

int Model::getMapWidth()
{
    return mapWidth;
}

int Model::getMapLength()
{
    return mapLength;
}

