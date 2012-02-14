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

QList<Bullet> Model::getUpdatedBullets()
{
    QMutexLocker locker(&mutex);
    QList<Bullet> ret(bullets);
    bullets.clear();

    return ret;
}

void Model::setUpdatedPlayers(QString json)
{
    QJson::Parser parser;
    QVariantMap result = parser.parse(json.toAscii()).toMap();

    foreach(QVariant obj, result["players"].toList()){
        Player p(obj.toMap());
        addUpdatedPlayer(p);
    }
}

void Model::setUpdatedBullets(QString json)
{
    QJson::Parser parser;
    QVariantMap result = parser.parse(json.toAscii()).toMap();

    foreach(QVariant obj, result["bullets"].toList()){
        Bullet b(obj.toMap());
        addUpdatedBullet(b);
    }
}

void Model::addUpdatedPlayer(Player p)
{
    QMutexLocker locker(&mutex);
    players.append(p);
}

void Model::addUpdatedBullet(Bullet b)
{
    QMutexLocker locker(&mutex);
    bullets.append(b);
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

QList<Player> Model::getAllPlayers()
{
    QMutexLocker locker(&mutex);
    QList<Player> cp(players);
    return cp;
}
