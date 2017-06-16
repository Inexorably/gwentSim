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

    //The round number (1, 2, 3).  Score is for player 1, 2 in positions 0, 1.
    int round;
    int score[2];

    //Ends the round.  Moves all cards to grave except for resilient.  Will trigger death effects, creates an event for round end.  If the game is not over, calls startRound.
    void endRound();

    //Starts a new round.  Mulligan and stuff depends on the round number, which is member variable round.
    //When the startRound event is triggered, things like olguerd and veteran effects activate.
    void startRound();

};











#endif // GWENTGAME_H
