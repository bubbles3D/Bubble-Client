#ifndef MODEL_H
#define MODEL_H

#include <QList>
#include <QPair>
#include <QSet>
#include <QMutex>
#include <QObject>
#include <QVariant>
#include <QTime>

#include "player.h"
#include "bullet.h"
#include "obstacles.h"

class Model: public QObject
{
    Q_OBJECT
public:
    static Model * getInstance();
    void addUpdatedPlayer(Player);
    void setUpdatedPlayers(QString json);
    QList<Player> getUpdatedPlayers();
    QList<Player> getAllPlayers();
    void addUpdatedBullet(Bullet);
    void setUpdatedBullets(QString json);
    QList<Bullet> getUpdatedBullets();
    void addUpdatedObstacles(Obstacles);
    void setUpdatedObstacles(QString json);
    QList<Obstacles> getUpdatedObstacles();
    void setName(QString n);
    QString getName();
    void updateKeys(QString name, bool state);
    void updateMouse(float x, float y, float z);
    void shot(float x, float y, float z);
    QList<QString> getClearedActors();


private:
    static Model * instance;
    Model();
    QMap<QString, Player> players;
    QMap<QString, Bullet> bullets;
    QMap<QString, Obstacles> obstacles;
    QString name;
    QSet<QString> toClear;
    mutable QMutex mutex;
    QTime mouseTimeout;
    void update();

signals:
    void keyChanged(QString name, bool state);
    void mouseChanged(float x, float y, float z);
    void shotEvent(float x, float y, float z);
};

#endif // MODEL_H
