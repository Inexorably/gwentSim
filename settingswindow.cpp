#include "settingswindow.h"
#include "ui_settingswindow.h"

SettingsWindow::SettingsWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsWindow)
{
    ui->setupUi(this);

    //Set the title.
    this->setWindowTitle("Settings");

    //Settings are seperated by newlines.
    /*bool multithread default 1
     *bool run n iterations default 0
     *int n iterations default 1000
     *bool run until error default 1
     *double error default 1
    */
    QString data;
    QFile infile(SETTINGSFILENAME);
    QStringList settingsList;

    if (infile.open(QFile::ReadOnly)){
        data = infile.readAll();
        settingsList = data.split("\n");
        infile.close();
    }
    else {
        qDebug() << "SettingsWindow::SettingsWindow(QWidget *parent) : File not found";
    }

    //Load the settings in the settingsList.
    ui->multithreadCheckBox->setChecked(static_cast<bool>(settingsList[0].toInt()));
    ui->nIterationsCheckBox->setChecked(static_cast<bool>(settingsList[1].toInt()));
    ui->nIterationsSpinBox->setValue(settingsList[2].toInt());
    ui->percentCheckBox->setChecked(static_cast<bool>(settingsList[3].toInt()));
    ui->percentSpinBox->setValue(settingsList[4].toDouble());
    ui->r1SpinBox->setValue(settingsList[5].toInt());
    ui->r2SpinBox->setValue(settingsList[6].toInt());
    ui->r3SpinBox->setValue(16-settingsList[5].toInt()-settingsList[6].toInt());
    ui->varyRoundCheckBox->setChecked(static_cast<bool>(settingsList[7].toInt()));
    ui->varyRoundSpinBox->setValue(settingsList[8].toInt());

    //Enable / disable interdependant widgets such as nIterations / percent.
    ui->nIterationsSpinBox->setEnabled(ui->nIterationsCheckBox->isChecked());
    ui->percentSpinBox->setEnabled(ui->percentCheckBox->isChecked());
    ui->varyRoundSpinBox->setEnabled(ui->varyRoundCheckBox->isChecked());
}

SettingsWindow::~SettingsWindow()
{
    delete ui;
}

void SettingsWindow::on_cancelButton_clicked(){
    close();
}

void SettingsWindow::on_okButton_clicked(){
    QFile outSettings(SETTINGSFILENAME);
    //Settings are seperated by newlines.
    /*bool multithread default 1
     *bool run n iterations default 0
     *int n iterations default 5000
     *bool run until error default 1
     *double error default 1
    */
    QString settings;
    settings += QString::number(static_cast<int>(ui->multithreadCheckBox->isChecked()))+"\n";
    settings += QString::number(static_cast<int>(ui->nIterationsCheckBox->isChecked()))+"\n";
    settings += QString::number(ui->nIterationsSpinBox->value())+"\n";
    settings += QString::number(static_cast<int>(ui->percentCheckBox->isChecked()))+"\n";
    settings += QString::number(ui->percentSpinBox->value())+"\n";
    settings += QString::number(ui->r1SpinBox->value())+"\n";
    settings += QString::number(ui->r2SpinBox->value())+"\n";
    settings += QString::number(static_cast<int>(ui->varyRoundCheckBox->isChecked()))+"\n";
    settings += QString::number(ui->varyRoundSpinBox->value());


    if(outSettings.open(QIODevice::WriteOnly | QIODevice::Truncate)){
        QTextStream out(&outSettings);
        out << settings;
        outSettings.close();
    }
    close();
}

void SettingsWindow::on_nIterationsCheckBox_clicked(){
    //If this box is now true, we set the percent box to false, disable the percent spin box, and enable the iterations spin box.
    if (ui->nIterationsCheckBox->isChecked()){
        ui->percentCheckBox->setChecked(false);
        ui->percentSpinBox->setEnabled(false);
        ui->nIterationsSpinBox->setEnabled(true);
    }
    else{
        //If this box is now false, set the nIterationsSpinBox to false and enable the percent widgets.
        ui->percentCheckBox->setChecked(true);
        ui->percentSpinBox->setEnabled(true);
        ui->nIterationsSpinBox->setEnabled(false);
    }
}

void SettingsWindow::on_percentCheckBox_clicked(){
    if (ui->percentCheckBox->isChecked()){
        ui->nIterationsCheckBox->setChecked(false);
        ui->percentSpinBox->setEnabled(true);
        ui->nIterationsSpinBox->setEnabled(false);
    }
    else{
        ui->nIterationsCheckBox->setChecked(true);
        ui->percentSpinBox->setEnabled(false);
        ui->nIterationsSpinBox->setEnabled(true);
    }
}

void SettingsWindow::on_r1SpinBox_valueChanged(int arg1){
    ui->r3SpinBox->setValue(16-ui->r2SpinBox->value()-arg1);
}

void SettingsWindow::on_r2SpinBox_valueChanged(int arg1){
    ui->r3SpinBox->setValue(16-ui->r1SpinBox->value()-arg1);
}

void SettingsWindow::on_varyRoundCheckBox_clicked(){
    ui->varyRoundSpinBox->setEnabled(ui->varyRoundCheckBox->isChecked());
}
