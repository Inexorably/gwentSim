#include "simthread.h"
#include "globals.h"
#include <QtCore>
#include "QProgressBar"
#include "globals.h"

#include <QDebug>

//Plagurising my code that I wrote the last time I remember using QThreads (2016, it's been a while).
//https://github.com/Inexorably/Hearthstone-Conquest-Sim/blob/master/simthread.cpp

SimThread::SimThread(const GwentScenario &gs) : pkg(gs){
    stop = false;

    //Initalise based on the settings in gwentCalc.set.
    QString data;
    QFile infile(SETTINGSFILENAME);
    QStringList settingsList;

    if (infile.open(QFile::ReadOnly)){
        data = infile.readAll();
        settingsList = data.split("\n");
        infile.close();
    }

    multithread = static_cast<bool>(settingsList[0].toInt());
    nChecked = static_cast<bool>(settingsList[1].toInt());
    n = settingsList[2].toInt();
    pChecked = static_cast<bool>(settingsList[3].toInt());
    p = settingsList[4].toDouble();

}
/*
void SimThread::percentChanged(int num){
    return;
}*/

void SimThread::run(){
    //Implementing iteration based run first.

    //The current progress, varies [0 100].
    //int prog = 0;
    //Update the progress bar every 1%.
    int onePercent = n/100;

    for (int g = 0; g < n; g++){

        //I have no idea what this is for, this is a remnant of old code (see above github link).
        //Avoid crashing.
        QMutex mutex;
        mutex.lock();
        if (this->stop)
            break;
        mutex.unlock();



        if (true || g % onePercent == 0){
            qDebug() << g;
            emit percentChanged(static_cast<double>(g)/n*100);
        }
    }

    //Done.
    emit percentChanged(100);

    //We will update the results to the table now.
    emit runComplete(1);

}
