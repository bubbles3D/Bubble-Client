#include <QtCore/QCoreApplication>
#include <QDebug>

#include "networkclient.h"
#include "model.h"
#include "gameapp.h"

int main(int argc, char *argv[])
{
    NetworkClient nc;
    nc.setName("naruto69");
    nc.startOn("134.214.167.50", 9001);
    QCoreApplication a(argc, argv);
    GameApp ga;
    ga.run();

    return a.exec();
}
