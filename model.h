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
    void updateKeys(QList<QPair<QString, QVariant> > k);

private:
    static Model * instance;
    Model();
    QList<Player> players;
    mutable QMutex mutex;

signals:
    void keys(QList<QPair<QString, QVariant> > k);

};

#endif // MODEL_H
