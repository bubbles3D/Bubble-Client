#include <QtCore/QCoreApplication>
#include <QDebug>

#include "networkclient.h"
#include "model.h"
#include "OgreEngine/OgreApp.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    OgreApp app;
    app.start();
    app.wait();

    //NetworkClient nc;
    //nc.setName("naruto69");
    //nc.startOn("134.214.167.50", 9001);

    //return a.exec();
    return 0;
}
