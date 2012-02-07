#include "appdialog.h"
#include "ui_appdialog.h"

AppDialog::AppDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AppDialog)
{
    ui->setupUi(this);
}

void AppDialog::accept()
{

}

void AppDialog::reject()
{

}

AppDialog::~AppDialog()
{
    delete ui;
}
