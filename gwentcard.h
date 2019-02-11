#ifndef GWENTCARD_H
#define GWENTCARD_H

#include <QString>

class GwentCard
{
public:
    GwentCard(QString tempName, int tempProvisions, double tempUnconditionalPoints);

    QString name;
    int provisions;
    double unconditionalPoints; //Points that are not conditional (ie dependant on things, like bloodlust).
};

#endif // GWENTCARD_H
