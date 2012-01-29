#ifndef GAMEAPP_H
#define GAMEAPP_H

#include <QObject>
#include "OgreEngine/OgreApp.h"
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
    OgreApp * thread;

};

#endif // GAMEAPP_H
