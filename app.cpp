#include <QtCore/QCoreApplication>
#include <QApplication>
#include <QMetaType>
#include <QDebug>

#include "appdialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    AppDialog app;

    app.setVisible(true);

    return a.exec();
}
