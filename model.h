#ifndef MODEL_H
#define MODEL_H

#include <QList>
#include <QPair>
#include <QMutex>
#include <QObject>
#include <QVariant>
#include <QTime>

#include "player.h"
#include "bullet.h"

class Model: public QObject
{
    Q_OBJECT
public:
    static Model * getInstance();
    void addUpdatedPlayer(Player);
    void setUpdatedPlayers(QString json);
    QList<Player> getUpdatedPlayers();
    void addUpdatedBullet(Bullet);
    void setUpdatedBullets(QString json);
    QList<Bullet> getUpdatedBullets();
    void setName(QString n);
    QString getName();
    void updateKeys(QString name, bool state);
    void updateMouse(float x, float y, float z);
    void shot(float x, float y, float z);

private:
    static Model * instance;
    Model();
    QList<Player> players;
    QList<Bullet> bullets;
    QString name;
    mutable QMutex mutex;
    QTime mouseTimeout;

signals:
    void keyChanged(QString name, bool state);
    void mouseChanged(float x, float y, float z);
    void shotEvent(float x, float y, float z);
};

#endif // MODEL_H
