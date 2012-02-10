#include "appdialog.h"
#include "ui_appdialog.h"

AppDialog::AppDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AppDialog)
{
    ui->setupUi(this);

    m = Model::getInstance();
    ga = new GameApp();

    connect(ga, SIGNAL(finished), this, SLOT(reject()));
}

void AppDialog::accept()
{
    m->setName(ui->PlayerName->text());

    NetworkClient * nc = new NetworkClient();
    nc->startOn(ui->ServerAddr->text(), ui->ServerPort->value());

    ga->run();

    setVisible(false);
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
