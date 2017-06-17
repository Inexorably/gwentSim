#ifndef GWENTCARD_H
#define GWENTCARD_H

#include <vector>
#include <QString>


class GwentCard
{
public:
    GwentCard(QString name, int basePower, int baseArmor);

private:
    //Basic variables for information of card.  Base power of -1 for spells.
    //Note that name is not constant because cards can be transformed (such as raging berserker).
    QString name;
    int basePower;
    int baseArmor;
    int currentArmor;
    int currentPower;

    //Rank can be bronze, silver, or gold.  Having char is more illustrative than using 0, 1, 2.  Ranks are b, s, g.
    char rank;

    //Boolean for revealed.  If true it is revealed, if false not revealed.  Initializes to false.
    bool revealed;

    //True if spying, else false.  Initializes to false.  Changes to false when no longer on opponent's side.
    bool spying;

    //The timer.  The first parameter is how many turns to tick the ratio is (such as 2 for vran).  The second is for not looping (Octivist, 0 or false), or looping (Vran, 1 or true).
    int timer[2];

    //Note that position is passed in the form of a 3d size_t var.
    //First number is board / graveyard / hand / deck respectively, 0 1 2 3.
    //Second number is row number (only relevant for board).  Melee, ranged, siege is 0 1 2.
    //Third number is index in the vector / deque.
    //Fourth number is which player's side it is on, same as gwentPlayer.id (1 or 2).
    size_t position[4];

    //A card can have different tags assigned to it.  Some are inherent such as cursed and regressing, and others are added such as adreneline rush.
    //These can be stored in a vector because the amount of tags can and will vary on cards.
    //These tags can be stored as strings.
    std::vector<QString> tags;

    //We need a function to activate the effect of the card.  Can change the function type at later date.  QString name is good identifier to use.
    void effect(const QString name);
};

#endif // GWENTCARD_H
