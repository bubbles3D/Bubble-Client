#include <QtCore/QCoreApplication>
#include "networkclient.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    NetworkClient nc;
    nc.startOn("134.214.167.130", 9001);

    return a.exec();
}
