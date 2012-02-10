#include <QDesktopServices>

#include "appdialog.h"
#include "ui_appdialog.h"

AppDialog::AppDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AppDialog)
{
    ui->setupUi(this);
    hosts = new QFile("hosts");

    if (hosts->open(QIODevice::ReadOnly))
    {
        QString str = hosts->readLine();
        QStringList host = str.split(':');

        ui->ServerAddr->setText(host[0]);
    }

    m = Model::getInstance();
    ga = new GameApp();

    connect(ga, SIGNAL(finished), this, SLOT(reject()));
}

void AppDialog::accept()
{
    m->setName(ui->PlayerName->text());

    if (!hosts->open(QIODevice::WriteOnly))
    {
        qDebug() << "Could not open hosts file";
    }
    else
    {
        QTextStream out(hosts);
        out << ui->ServerAddr->text() << ":" << ui->ServerPort->value();
    }

    NetworkClient * nc = new NetworkClient();
    nc->startOn(ui->ServerAddr->text(), ui->ServerPort->value());

    ga->run();

    setVisible(false);
    hosts->close();
}

void AppDialog::reject()
{
    setVisible(false);
    exit(0);
}

AppDialog::~AppDialog()
{
    delete ui;
}
