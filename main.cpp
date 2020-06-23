// main.cpp
// Author: Zdenek Zeman
// Last change: 15-7-18

#include "Game.h"
//#include "Deck.h"

int main()
{
    Game game;
    
    game.deposit();
    game.bettingRound();
    game.play();
    
    //game.printInfo();

    return 0;
}