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

void Model::setUpdatedPlayers(QString json)
{
    //QMutexLocker locker(&mutex);
    QJson::Parser parser;
    QVariantMap result = parser.parse(json.toAscii()).toMap();
    QSet<QString> diff = players.keys().toSet();

    toClear.clear();

    foreach(QVariant obj, result["players"].toList()){
        Player p(obj.toMap());
        addUpdatedPlayer(p);
        diff.remove(p.name);
    }

    foreach(QString s, diff){
        players.remove(s);
    }

    toClear.unite(diff);

    qDebug() << "plop " << toClear;
}

void Model::setUpdatedBullets(QString json)
{
    //QMutexLocker locker(&mutex);
    QJson::Parser parser;
    QVariantMap result = parser.parse(json.toAscii()).toMap();
    QSet<QString> diff = bullets.keys().toSet();

    toClear.clear();

    foreach(QVariant obj, result["bullets"].toList()){
        Bullet b(obj.toMap());
        addUpdatedBullet(b);
        diff.remove(b.name);
    }

    foreach(QString s, diff){
        bullets.remove(s);
    }

    toClear.unite(diff);

    qDebug() << "plopbullets " << toClear;
}

void Model::addUpdatedPlayer(Player p)
{
    QMutexLocker locker(&mutex);
    players.insert(p.name, p);
}

void Model::addUpdatedBullet(Bullet b)
{
    QMutexLocker locker(&mutex);
    bullets.insert(b.name, b);
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

    return ret;
}

