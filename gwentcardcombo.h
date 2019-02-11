#ifndef GWENTCARDCOMBO_H
#define GWENTCARDCOMBO_H

#include "gwentcard.h"

#include <vector>

//For storing combinations of gwentCards and the combined points power.

class GwentCardCombo
{
public:
    GwentCardCombo();

    std::vector<GwentCard> cards;

    //Can add more types of points such as bloodlust / assumed turns in future.
    double unconditionalPoints;
};

#endif // GWENTCARDCOMBO_H
