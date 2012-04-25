#include <qjson/parser.h>
#include <QVariant>
#include <QDebug>
#include <QTimer>
#include <cstring>

#include "model.h"

#include "OgreEngine/playerHUDManagement.h"
#include "OgreEngine/objectsManager.h"

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

QList<Flag> Model::getUpdatedFlags()
{
    QMutexLocker locker(&mutex);

    QList<Flag> ret;
    foreach(Flag* f, flags.values()){
        if (flagsToUpdate.contains(f->id))
        {
            ret.append(*f);
        }
    }

    flagsToUpdate.clear();

    return ret;
}

QList<Flag> Model::getAllFlags()
{
    QMutexLocker locker(&mutex);

    QList<Flag> ret;
    foreach(Flag* f, flags.values()){
        ret.append(*f);
    }

    return ret;
}


QList<Flag> Model::getNewFlags()
{
    QMutexLocker locker(&mutex);

    QList<Flag> ret;
    foreach(QString id, newFlags){
        ret.append(*(flags.value(id)));
    }

    newFlags.clear();
    return ret;
}

const QList<QPair<QString, QString> > Model::getFlagsToAttach()
{
    QMutexLocker locker(&mutex);

    QList<QPair<QString, QString> > tmp(flagsToAttach);
    flagsToAttach.clear();

    return tmp;
}

const QList<QString> Model::getFlagsToDettach()
{
    QMutexLocker locker(&mutex);

    QList<QString> tmp(flagsToDettach);
    flagsToDettach.clear();

    return tmp;
}

void Model::setUpdatedPlayers(QString json)
{
    QJson::Parser parser;
    QVariantMap result = parser.parse(json.toAscii()).toMap();

    foreach(QVariant obj, result["players"].toList()){
        if (obj.toMap()["name"].toString() == this->name)
            this->id = obj.toMap()["id"].toInt();

        //If it's us
        if (obj.toMap()["id"] == this->id)
        {
            //Check if life has changed
            if (life != 0 && obj.toMap().contains("life") && obj.toMap()["life"].toInt() < life)
            {
                //In case of life going down trigger injur animation
                qDebug() << "life flash" << life << " " <<obj.toMap()["life"].toInt();
                PlayerHUDManagement::touched();
            }
            life = obj.toMap()["life"].toInt();
        }        

        //If a player is to be set a flag
        if (obj.toMap().contains("flag") &&
                //players.value(obj.toMap()["id"].toString())->flag == 0 &&
                obj.toMap()["flag"].toString() != "0")
        {
            QPair<QString, QString> pair(obj.toMap()["id"].toString(), obj.toMap()["flag"].toString());
            flagsToAttach.append(pair);
        }

        //Remove a flag
        if (obj.toMap().contains("flag") &&
                players.contains(obj.toMap()["id"].toString()) &&
                players.value(obj.toMap()["id"].toString())->flag != 0 &&
                obj.toMap()["flag"].toString() == "0")
        {
            qDebug()<<"Model: detach flag";
            flagsToDettach.append(obj.toMap()["id"].toString());
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

void Model::setUpdatedFlags(QString json)
{
    QJson::Parser parser;
    QVariantMap result = parser.parse(json.toAscii()).toMap();

    foreach(QVariant obj, result["flags"].toList()){        
        updateFlag(obj);
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

void Model::updateFlag(QVariant data)
{
    QMutexLocker locker(&mutex);
    QVariantMap obj = data.toMap();

    flagsToUpdate.append(obj["id"].toString());

    if (flags.contains(obj["id"].toString()))
    {
        flags[obj["id"].toString()]->update(obj);        
    }
    else
    {
        Flag* o = new Flag(data.toMap());
        flags.insert(o->id, o);
        newFlags.append(o->id);
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
    emit keyChanged(name, state);
    //qDebug() << "Emited keys signal";
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
            flagsToDettach.removeOne(obj.toString());
        }
        else if(bullets.contains(obj.toString()))
        {
            delete bullets.take(obj.toString());
        }
        else if(obstacles.contains(obj.toString()))
        {
            delete obstacles.take(obj.toString());
        }
        else if(flags.contains(obj.toString()))
        {
            delete flags.take(obj.toString());
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

void Model::endOfTime()
{
    flagsToDettach.clear();
    flagsToAttach.clear();

    PlayerHUDManagement::displayStats();
    QTimer::singleShot(pauseTime * 1000, this, SLOT(endOfPause()));
}

void Model::endOfPause()
{
    PlayerHUDManagement::hideStats();
}

void Model::setGameInfo(QString json)
{
    QMutexLocker locker(&mutex);
    QJson::Parser parser;
    QVariantMap result = parser.parse(json.toAscii()).toMap();
    QMap<QString, QVariant> game = result["game"].toMap();

    pauseTime = game["pauseTime"].toFloat();
    gameType = game["gameType"].toInt();
    gameTime = game["gameTime"].toFloat();

    QTimer::singleShot(gameTime * 1000, this, SLOT(endOfTime()));

    elapsedGameTime.restart();
}

void Model::setTeamInfo(QString json)
{

}

float Model::getRemainingTime()
{
    float time = gameTime - (elapsedGameTime.elapsed() / 1000);

    return time >= 0.0 ? time : 0.0;
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

