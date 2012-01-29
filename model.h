#ifndef MODEL_H
#define MODEL_H

#include <QList>
#include <QPair>
#include <QMutex>
#include <QObject>
#include <QVariant>

#include "player.h"

class Model: public QObject
{
    Q_OBJECT
public:
    static Model * getInstance();
    void setUpdatedPlayers(QList<Player> p);
    void setUpdatedPlayers(QString json);
    void addUpdatedPlayer(Player);
    QList<Player> getUpdatedPlayers();
    void setName(QString n);
    QString getName();
    void updateKeys(QString name, bool state);

private:
    static Model * instance;
    Model();
    QList<Player> players;
    QString name;
    mutable QMutex mutex;

signals:
    void keyChanged(QString name, bool state);

};

#endif // MODEL_H
