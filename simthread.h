#ifndef SIMTHREAD_H
#define SIMTHREAD_H

#include "gwentscenario.h"

#include <QtCore>

//Stealing this from my Hearthstone Conquest Sim as apparently I figured out how to use QThread at the time.
//Source with reference code in other files:
//https://github.com/Inexorably/Hearthstone-Conquest-Sim/blob/master/simthread.h

class SimThread :public QThread{
    Q_OBJECT

    public:

        SimThread(const GwentScenario &gs);
        void run();
        bool stop;

    private:
        //Run for n iterations or until relative error is acceptable.  Error is in percent (p).
        int n;
        double p;
        bool nChecked;
        bool pChecked;
        bool multithread;

        GwentScenario pkg;  //Bundled deck and combo information.

    signals:
        void percentChanged(int);
        void runComplete(int);
};

#endif // SIMTHREAD_H
