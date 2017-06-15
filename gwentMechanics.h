#ifndef GWENTMECHANICS_H
#define GWENTMECHANICS_H

//This will have the gwent mechanics and related functions, such as damage and strengthen.

#include "gwentGame.h"

//Discard the card to graveyard from hand.  Takes the index in hand and uses that information to send to the graveyard.
//Takes the player as a passed by reference input such that we can remove and send the card to the graveyard.
void discardFromHand(size_t position, gwentPlayer &player);
void discardFromDeck(size_t position, gwentPlayer &player);

//While draw is a member function of gwentPlayer, it is also a mechanic from cards such as spies.
void draw(gwentPlayer &player);

//Takes the target and damage amount as an input.  We pass the target by reference.  If the target dies, we move it to graveyard / banish it.
void damage(gwentCard &target, int amount, gwentBoard &board);

//Takes the target and weaken amount as an input.  We pass the target by reference.  If the target dies, we move it to graveyard / banish it.
void weaken(gwentCard &target, int amount, gwentBoard &board);

//Strengthen the target for the amount.  The board will not change with this effect, so we don't need to pass it.
void strengthen(gwentCard &target, int amount);

//Boost the target for the amount.  The board will not change with this effect, so we don't need to pass it.
void boost(gwentCard &target, int amount);


























#endif // GWENTMECHANICS_H
