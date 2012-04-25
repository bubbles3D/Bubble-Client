#ifndef MODEL_H
#define MODEL_H

#include <QList>
#include <QPair>
#include <QSet>
#include <QMutex>
#include <QObject>
#include <QVariant>
#include <QTime>
#include <QColor>

#include "player.h"
#include "bullet.h"
#include "obstacles.h"
#include "flag.h"

class Model: public QObject
{
    Q_OBJECT
public:
    int mapWidth, mapLength;

    static Model * getInstance();

    //Players
    void addUpdatedPlayer(Player);
    void setUpdatedPlayers(QString json);
    QList<Player> getUpdatedPlayers();
    QList<Player> getAllPlayers();
    void updatePlayer(QVariant data);

    //Bullets
    void addUpdatedBullet(Bullet);
    void setUpdatedBullets(QString json);
    QList<Bullet> getUpdatedBullets();
    void updateBullet(QVariant data);

    //Obstacles
    void addUpdatedObstacles(Obstacles);
    void setUpdatedObstacles(QString json);
    QList<Obstacles> getUpdatedObstacles();
    void updateObstacle(QVariant data);

    //Flags
    void addUpdatedFlag(Flag);
    void setUpdatedFlags(QString json);
    QList<Flag> getUpdatedFlags();
    void updateFlag(QVariant data);
    const QList<QPair<QString, QString> > getFlagsToAttach();
    const QList<QString> getFlagsToDettach();
    QList<Flag> getAllFlags();
    QList<Flag> getNewFlags();

    void setName(QString n);
    QString getName();
    void setColor(QColor c);
    QColor getColor();
    void updateKeys(QString name, bool state);
    void updateMouse(float x, float y, float z);
    void shot(float x, float y, float z);
    QList<QString> getClearedActors();

    //Map
    void setMap(QString json);
    int getMapWidth();
    int getMapLength();

    //Game
    void setGameInfo(QString json);
    void setTeamInfo(QString json);
    float getRemainingTime();

    void setToClear(QString json);


private:
    static Model * instance;
    Model();
    QMap<QString, Player*> players;
    QMap<QString, Bullet*> bullets;
    QMap<QString, Obstacles*> obstacles;
    QMap<QString, Flag*> flags;
    QList<QString> newFlags;
    QList<QPair<QString, QString> > flagsToAttach;
    QList<QString> flagsToDettach;
    QList<QString> flagsToUpdate;
    QString name;
    QSet<QString> toClear;
    QColor color;
    QTime elapsedGameTime;
    int life, id;
    mutable QMutex mutex;
    QTime mouseTimeout;
    void update();
    float pauseTime;
    float gameTime;
    int gameType;

signals:
    void keyChanged(QString name, bool state);
    void mouseChanged(float x, float y, float z);
    void shotEvent(float x, float y, float z);

public slots:
    void endOfTime();
    void endOfPause();
};

#endif // MODEL_H
