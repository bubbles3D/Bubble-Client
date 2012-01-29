#include "gameapp.h"



GameApp::GameApp(QObject *parent) :
    QObject(parent)
{
    thread = new QThread();
    connect(thread, SIGNAL(finished()), this, SLOT(endOfThread()));
    connect(thread, SIGNAL(terminated()), this, SLOT(endOfThread()));
}


void GameApp::endOfThread()
{
    delete thread;
}

void GameApp::run()
{
    NetworkClient nc;
    nc.setName("naruto69");
    nc.startOn("134.214.167.50", 9001);

    thread->start();
}
