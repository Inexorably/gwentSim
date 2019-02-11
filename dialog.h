#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QString>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(const QString s, QWidget *parent = nullptr);
    ~Dialog();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
