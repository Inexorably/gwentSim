#ifndef GWENTMECHANICS_H
#define GWENTMECHANICS_H

//This will have the gwent mechanics and related functions, such as damage and strengthen.


#include "gwentGame.h"

//Define global strings such as const char GOLD = 'g' here.  Tags also go here.
const QString TAG_RESILIENT = "Resilient";

//List of keywords that are tags and will not have an explicit function:
/*http://gwentify.com/guides/gwent-keyword-list-gwent-mechanics/
 * Ally, Ambush, Bond, Brave, Crewmen X, Deathwish, Deploy, Disloyal, Effort, Enemy, Fresh crew, Orders
 * Retaliation, Regressing, Shield (like Quen), Trio, Turn End, Turn Start, Veteran, Weaken
 *
 *
 *
 *
*/

//Adds a tag to the target card (such as resilient, regressing, etc).
void addTag(gwentCard &target, const QString tag);

//Adds armor to the target.
void addArmor(gwentCard &target, const int amount);

//Boost the target for the amount.  The board will not change with this effect, so we don't need to pass it.
void boost(gwentCard &target, const int amount);

//Banish the card at the position.
void banish(gwentCard &target);

//Consume functions.  If the target is in the hand / field it is sent to grave, else if in grave it is banished.  Note: should activate a "consumed trigger", as other mechanics shall with their triggers.
void consume(gwentCard &target);

//Takes the target and damage amount as an input.  We pass the target by reference.  If the target dies, we move it to graveyard / banish it.
void damage(gwentCard &target, const int amount, gwentBoard &board);

//Demote the card to silver if gold.  If bronze stays bronze.
void demote(gwentCard &target);

//Destroy the target.
void destroy(gwentCard &target, gwentPlayer &player);

//Discard the card to graveyard from hand.  Takes the index in hand and uses that information to send to the graveyard.
//Takes the player as a passed by reference input such that we can remove and send the card to the graveyard.
//We could store the card position in the card variable.  However, this is not only duplicate information but will be a huge slowdown in running many simulations.
//Thus, functions such as this require us to pass the position.
void discard(gwentCard &target, gwentPlayer &player);

//While draw is a member function of gwentPlayer, it is also a mechanic from cards such as spies.
void draw(gwentPlayer &player);

//Heal the target.  Can take just the card as input as will not change the board.
void heal(gwentCard &target);

//Returns the position of the highest card on the board.
std::vector<int> highest(gwentPlayer &player);

//Locks the target, does not affect board.
void lock(gwentCard &target);

//Finds the position of the lowest card on the board.
std::vector<int> lowest(gwentPlayer &player);

//Mulligan the card at the target position (in hand).
void mulligan(const size_t index, gwentPlayer &player);

//Promote: convert the target to gold until the end of the round.
void promote(gwentCard &target);

//Reset the unit to its base power.
void reset(gwentCard &target);

//Resurrect the target from the graveyard.
void resurrect(gwentCard &target, gwentPlayer &player);

//Reveal the target.
void reveal(gwentCard &target);

//Spawn the target at the position.  Adds the card to the game and plays it.  Note that not all of position is needed (it can only be on the board, so need side, row number, and index, but we take the normal size for consistency.
void spawn(gwentCard &target, const size_t position[4]);

//Summon the card from the deck.  Similair to spawn, but will remove the copy from the player's deck.
void summon(gwentCard &target, const size_t position[4], gwentPlayer &player);

//Transform the card into a different card.
void transform(gwentCard &target, const gwentCard transformedTo);





//Strengthen the target for the amount.  The board will not change with this effect, so we don't need to pass it.
void strengthen(gwentCard &target, const int amount);

//Takes the target and weaken amount as an input.  We pass the target by reference.  If the target dies, we move it to graveyard / banish it.
void weaken(gwentCard &target, gwentPlayer &player, const int amount);






























#endif // GWENTMECHANICS_H
