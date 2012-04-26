#include <QDesktopServices>

#include "appdialog.h"
#include "ui_appdialog.h"

AppDialog::AppDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AppDialog)
{
    //set default color (white)
    QColor c(255, 255, 255);
    qchooser = new QColorDialog(c, this);

    //Default color in model
    m = Model::getInstance();
    m->setColor(c);

    ui->setupUi(this);

    //Default color on button
    this->ui->colorButton->setStyleSheet("* { background-color: rgb("+
                                      QString::number(255)+","+
                                      QString::number(255)+","+
                                      QString::number(255)+")}");

    //Save to file
    hosts = new QFile("hosts");
    if (hosts->open(QIODevice::ReadOnly))
    {
        QString str = hosts->readLine();
        QStringList host = str.split(':');

        ui->PlayerName->setText(host[0]);
        ui->ServerAddr->setText(host[1]);
        hosts->close();
    }

    nc = new NetworkClient();
    ga = new GameApp();
    connect(ga, SIGNAL(destroyed()), this, SLOT(reject()));    
}

void AppDialog::accept()
{
    m->setName(ui->PlayerName->text());
    nc->setName(ui->PlayerName->text());

    if (!hosts->open(QIODevice::WriteOnly))
    {
        qDebug() << "Could not open hosts file";
    }
    else
    {
        QTextStream out(hosts);
        out << ui->PlayerName->text() << ":" << ui->ServerAddr->text() << ":" << ui->ServerPort->value();
        hosts->close();
    }

    nc->startOn(ui->ServerAddr->text(), ui->ServerPort->value());
    connect(nc, SIGNAL(networkReady()), ga, SLOT(run()));

    //ga->run();

    setVisible(false);
    hosts->close();
}

void AppDialog::colorChosen(QColor color)
{
    int r, g, b;
    color.getRgb(&r, &g, &b);

    this->ui->colorButton->setStyleSheet("* { background-color: rgb("+
                                      QString::number(r)+","+
                                      QString::number(g)+","+
                                      QString::number(b)+")}");

    m->setColor(color);
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

void AppDialog::on_colorButton_clicked()
{
    qchooser->open(this, SLOT(colorChosen(QColor)));
}
