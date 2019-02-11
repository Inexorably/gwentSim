#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include "globals.h"

#include <QDialog>
#include <QFile>
#include <QDebug>

namespace Ui {
class SettingsWindow;
}

class SettingsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsWindow(QWidget *parent = nullptr);
    ~SettingsWindow();

private slots:
    void on_cancelButton_clicked();

    void on_okButton_clicked();

    void on_nIterationsCheckBox_clicked();

    void on_percentCheckBox_clicked();

    void on_r1SpinBox_valueChanged(int arg1);

    void on_r2SpinBox_valueChanged(int arg1);

    void on_varyRoundCheckBox_clicked();

private:
    Ui::SettingsWindow *ui;
};

#endif // SETTINGSWINDOW_H
