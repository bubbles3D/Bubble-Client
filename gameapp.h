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

public slots:
    void endOfThread();
    void run();

 private:
    OgreApp * thread;

};

#endif // GAMEAPP_H
