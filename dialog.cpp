#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(const QString s, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->messageLabel->setAlignment(Qt::AlignCenter);
    ui->messageLabel->setText(s);
}

Dialog::~Dialog()
{
    delete ui;
}
