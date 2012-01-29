#include "gameapp.h"



GameApp::GameApp(QObject *parent) :
    QObject(parent)
{
    thread = new OgreApp();
    connect(thread, SIGNAL(finished()), this, SLOT(endOfThread()));
    connect(thread, SIGNAL(terminated()), this, SLOT(endOfThread()));
}


void GameApp::endOfThread()
{
    qDebug() << "lol";
    delete thread;
}

void GameApp::run()
{
    thread->start();
}
