#include "gwentGame.h"

/*Random for later:
 *     //Random Source: https://stackoverflow.com/questions/5008804/generating-random-integer-from-a-range
    //Usage: auto random_integer = uni(rng);
    std::random_device rd;     // only used once to initialise (seed) engine
    std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
    std::uniform_int_distribution<int> uni(0, int(deck.size()-1)); // guaranteed unbiased
    auto random_integer = uni(rng);
    */

/***********************************************************************************************/
/*******************************Implementing gwentPlayer functions******************************/
/***********************************************************************************************/

//This function returns the current total number of points a player has.
int gwentPlayer::getOwnPointTotal(){
    //We need to get the correct side of the board.
    gwentRows correctSide;
    if (id == 1){
        correctSide = board.playerOneSide;
    }
    else{
        correctSide = board.playerTwoSide;
    }

    //We now have the correct side stored.  Could add melee ranged and siege to array / vector but not worth the time.
    int totalPower = 0;
    for (size_t i = 0; i < correctSide.melee.size(); i++){
        totalPower += correctSide.melee[i].currentPower;
    }
    for (size_t i = 0; i < correctSide.ranged.size(); i++){
        totalPower += correctSide.ranged[i].currentPower;
    }
    for (size_t i = 0; i < correctSide.siege.size(); i++){
        totalPower += correctSide.siege[i].currentPower;
    }
    return totalPower;
}


//This function returns the current total number of points a player's opponent has.
int gwentPlayer::getEnemyPointTotal(){
    //We need to get the correct side of the board.
    gwentRows correctSide;
    if (id == 2){
        correctSide = board.playerOneSide;
    }
    else{
        correctSide = board.playerTwoSide;
    }

    //We now have the correct side stored.  Could add melee ranged and siege to array / vector but not worth the time.
    int totalPower = 0;
    for (size_t i = 0; i < correctSide.melee.size(); i++){
        totalPower += correctSide.melee[i].currentPower;
    }
    for (size_t i = 0; i < correctSide.ranged.size(); i++){
        totalPower += correctSide.ranged[i].currentPower;
    }
    for (size_t i = 0; i < correctSide.siege.size(); i++){
        totalPower += correctSide.siege[i].currentPower;
    }
    return totalPower;
}

//The player draws a card from their deck.
void gwentPlayer::draw(){
    //Return if deck is empty.
    if (deck.size() == 0)
        return;

    //Draw the top card of the deck.
    hand.push_back(deck.front());
    deck.pop_front();
}

//Shuffle the deck.
void gwentPlayer::shuffleDeck(){
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(deck.begin(), deck.end(), std::default_random_engine(seed));
}

/***********************************************************************************************/
/*******************************Implementing gwentGame functions********************************/
/***********************************************************************************************/

//Get the id of the current turn player.
int gwentGame::getTurnPlayerId(){
    return turnPlayerId;
}

//Change the current turn player.
void gwentGame::changeTurnPlayer(){
    if (turnPlayerId == 1){
        //We update the board of the player going in next.
        playerTwo.board = playerOne.board;
        turnPlayerId == 2;
    }
    else{
        playerOne.board == playerTwo.board;
        turnPlayerId == 1;
    }
}
