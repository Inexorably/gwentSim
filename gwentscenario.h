#ifndef GWENTSCENARIO_H
#define GWENTSCENARIO_H

#include "gwentcard.h"
#include "gwentcardcombo.h"
#include <vector>

//A class to ecapsulate the deck and combos members so that we can pass one object around.

class GwentScenario
{
public:
    GwentScenario(const std::vector<GwentCard> &d, const std::vector<GwentCardCombo> &c);

    std::vector<GwentCard> deck;
    std::vector<GwentCardCombo> combos;
};

#endif // GWENTSCENARIO_H
