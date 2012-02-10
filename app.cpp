#include <QtCore/QCoreApplication>
#include <QMetaType>
#include <QDebug>

#include "networkclient.h"
#include "model.h"
#include "gameapp.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Model * m = Model::getInstance();
    NetworkClient nc;
    nc.setName("naruto92");
    m->setName("naruto92");


    nc.startOn("10.42.43.58", 9001);

    GameApp ga;
    ga.run();

    return a.exec();
}
