#include "gwentscenario.h"

GwentScenario::GwentScenario(const std::vector<GwentCard> &d, const std::vector<GwentCardCombo> &c){
    deck = d;
    combos = c;
}
