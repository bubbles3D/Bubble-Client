#include <qjson/parser.h>
#include <QVariant>
#include <QDebug>
#include <cstring>

#include "model.h"

#include "OgreEngine/playerHUDManagement.h"

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

    QList<Player> ret;

    foreach(Player* p, players.values()){
        ret.append(*p);
    }

    return ret;
}

QList<Bullet> Model::getUpdatedBullets()
{
    QMutexLocker locker(&mutex);

    QList<Bullet> ret;

    foreach(Bullet* b, bullets.values()){
        ret.append(*b);
    }

    return ret;
}

QList<Obstacles> Model::getUpdatedObstacles()
{
    QMutexLocker locker(&mutex);

    QList<Obstacles> ret;
    foreach(Obstacles* o, obstacles.values()){
        ret.append(*o);
    }

    return ret;
}


void Model::setUpdatedPlayers(QString json)
{
    QJson::Parser parser;
    QVariantMap result = parser.parse(json.toAscii()).toMap();

    foreach(QVariant obj, result["players"].toList()){
        if (obj.toMap()["name"].toString() == this->name)
            this->id = obj.toMap()["id"].toInt();

        if (obj.toMap()["id"] == this->id)
        {
            if (life != 0 && obj.toMap().contains("life") && obj.toMap()["life"].toInt() < life)
            {
                qDebug() << "life flash" << life << " " <<obj.toMap()["life"].toInt();
                PlayerHUDManagement::touched();
            }
            life = obj.toMap()["life"].toInt();
        }

        updatePlayer(obj);
    }
}

void Model::setUpdatedBullets(QString json)
{
    QJson::Parser parser;
    QVariantMap result = parser.parse(json.toAscii()).toMap();

    foreach(QVariant obj, result["bullets"].toList()){
        updateBullet(obj);
    }
}

void Model::setUpdatedObstacles(QString json)
{
    QJson::Parser parser;
    QVariantMap result = parser.parse(json.toAscii()).toMap();
    QMap<QString, QVariant> field = result["field"].toMap();

    foreach(QVariant obj, field["obstacles"].toList()){
        updateObstacle(obj);
    }
}

/*void Model::addUpdatedPlayer(Player p)
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
}*/

void Model::updatePlayer(QVariant data)
{
    QMutexLocker locker(&mutex);
    QVariantMap obj = data.toMap();

    if (players.contains(obj["id"].toString()))
    {
        players[obj["id"].toString()]->update(obj);
    }
    else
    {
        qDebug() << "Created player with ID :" << obj["id"].toString();
        Player* p = new Player(data.toMap());
        players.insert(p->id, p);
    }
}

void Model::updateBullet(QVariant data)
{
    QMutexLocker locker(&mutex);
    QVariantMap obj = data.toMap();

    if (bullets.contains(obj["id"].toString()))
    {
        bullets[obj["id"].toString()]->update(obj);
    }
    else
    {
        Bullet* b = new Bullet(data.toMap());
        bullets.insert(b->id, b);
    }
}

void Model::updateObstacle(QVariant data)
{
    QMutexLocker locker(&mutex);
    QVariantMap obj = data.toMap();

    if (obstacles.contains(obj["id"].toString()))
    {
        obstacles[obj["id"].toString()]->update(obj);
    }
    else
    {
        Obstacles* o = new Obstacles(data.toMap());
        obstacles.insert(o->id, o);
    }
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
    //Send state to server
    emit keyChanged(name, state);

    //Update local version

    //A key is pressed
    if (state)
    {
        if (name == "UP"){
            //TODO
        }else if (name == "RIGHT"){
            //TODO
        }else if (name == "LEFT"){
            //TODO
        }else if (name == "DOWN"){
            //TODO
        }else{
            //Key unknown
        }
    //A key has been realesed
    }else{
        if (name == "UP"){
            //TODO
        }else if (name == "RIGHT"){
            //TODO
        }else if (name == "LEFT"){
            //TODO
        }else if (name == "DOWN"){
            //TODO
        }else{
            //Key unknown
        }
    }

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
        mouseTimeout.restart();
    }
}

void Model::shot(float x, float y, float z)
{
    emit shotEvent(x, y, z);
    //qDebug() << "shotEvent sent";
}

/* Deprecated */
QList<Player> Model::getAllPlayers()
{
    QMutexLocker locker(&mutex);
    QList<Player> ret;

    foreach(Player* p, players.values()){
        ret.append(*p);
    }

    return ret;
}

QList<QString> Model::getClearedActors(){
    QMutexLocker locker(&mutex);
    QList<QString> ret = toClear.toList();

    toClear.clear();

    return ret;
}

void Model::setToClear(QString json)
{
    QJson::Parser parser;
    QVariantMap result = parser.parse(json.toAscii()).toMap();

    foreach(QVariant obj, result["toClear"].toList()){
        toClear.insert(obj.toString());

        if(players.contains(obj.toString()))
        {
            delete players.take(obj.toString());
        }
        else if(bullets.contains(obj.toString()))
        {
            delete bullets.take(obj.toString());
        }
        else if(obstacles.contains(obj.toString()))
        {
            delete obstacles.take(obj.toString());
        }
    }
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

void Model::setColor(QColor c)
{
    QMutexLocker locker(&mutex);
    color = c;
}

QColor Model::getColor()
{
    return color;
}

