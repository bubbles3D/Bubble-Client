#include <QtCore/QCoreApplication>
#include <QDebug>

#include "networkclient.h"
#include "model.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    NetworkClient nc;
    nc.setName("naruto69");
    nc.startOn("134.214.167.50", 9001);

    return a.exec();
}
