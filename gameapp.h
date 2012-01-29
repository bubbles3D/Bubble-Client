#ifndef GAMEAPP_H
#define GAMEAPP_H

#include <QObject>
#include <QThread>
#include "networkclient.h"

class GameApp : public QObject
{
    Q_OBJECT
public:
    explicit GameApp(QObject *parent = 0);
    void run();

signals:

public slots:
    void endOfThread();

 private:
    QThread * thread;

};

#endif // GAMEAPP_H
