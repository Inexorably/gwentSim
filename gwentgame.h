#ifndef GWENTGAME_H
#define GWENTGAME_H

#include <string>
#include <vector>
#include <deque>
#include <random>
#include <algorithm>
#include <QString>
#include <chrono>

//The struct for cards.
struct gwentCard{
    //Basic variables for information of card.
    const QString name;
    int basePower;
    int currentPower;

    //A card can have different tags assigned to it.  Some are inherent such as cursed and regressing, and others are added such as adreneline rush.
    //These can be stored in a vector because the amount of tags can and will vary on cards.
    //These tags can be stored as strings.
    std::vector<QString> tags;

    //We need a function to activate the effect of the card.  Can change the function type at later date.  QString name is good identifier to use.
    void effect(const QString name);

};

//The struct for the board for both players.  We probably want the rows inside one structure in case we need to loop through them for card effects.
struct gwentBoard{
    //We can tell the players apart by the int id in gwentPlayer struct.
    gwentRows playerOneSide;
    gwentRows playerTwoSide;
};

//These will contain the cards on each row for each player.  Should it be seperated for each player?
//Speed and ease of use probably outweigh a little memory.
struct gwentRows{
    std::vector<gwentCard> melee;
    std::vector<gwentCard> ranged;
    std::vector<gwentCard> siege;
};

//We likely want a struct for each player.
struct gwentPlayer{
    //Should have an identifial variable to tell players apart.
    int id;

    //This struct should contain deck, and hand.  Note that the top of the deck is deck.front();.
    std::deque<gwentCard> deck;
    std::vector<gwentCard> hand;

    //Contains the gwentBoard.  Note: this doubles memory usage in this particular area (as we create two boards).  Figure out if this is very impactful compared to the deck vectors and stuff.
    gwentBoard board;

    //The graveyard and banished zone.
    std::vector<gwentCard> graveyard;
    std::vector<gwentCard> banished;

    //Some utility functions for the player.  Think, how should AI be stored.  Prob will run in game?
    int getOwnPointTotal();
    int getEnemyPointTotal();
    void draw();
    void shuffleDeck();


};


/*
This struct is the overarching class for a given game, meaning that when running the monte carlo search tree and
creating simulations in parallel, we will aim for this class to be the one used.
Note: Should include a history vector of moves done (at very least on first simulated turn) such that we can load it into the global table of moves
such that the ai can figure out what move is the best.
This struct should contain a board for both players.
*/
struct gwentGame{
    //We need two players for the game.  It is fine to have them hard coded in this style and not in a structure because there will only ever be two players in the game.
    //The ai will be passed stuff it needs such as the board.
    gwentPlayer playerOne;
    gwentPlayer playerTwo;

    //The current (turn) player.
    int turnPlayerId;
    int getTurnPlayerId();
    void changeTurnPlayer();


};











#endif // GWENTGAME_H
