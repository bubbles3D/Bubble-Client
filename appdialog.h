#ifndef APPDIALOG_H
#define APPDIALOG_H

#include <QDialog>

namespace Ui {
    class AppDialog;
}

class AppDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AppDialog(QWidget *parent = 0);
    ~AppDialog();

public slots:
    void accept();
    void reject();

private:
    Ui::AppDialog *ui;
};

#endif // APPDIALOG_H
