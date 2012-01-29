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
    nc.setName("naruto42");
    m->setName("naruto42");


    nc.startOn("134.214.167.50", 9001);

    GameApp ga;
    ga.run();

    return a.exec();
}
