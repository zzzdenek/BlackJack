// Player.h
// Author: Zdenek Zeman
// Last change: 15-7-18

#ifndef PLAYER_H
#define PLAYER_H

#include "Box.h"

#include <string>
#include <memory>

using std::string;

class Player
{
private:
    string name_;
    int bankroll_;

    Player(const Player &copy) {};

public:
    Player() : name_("Player"), bankroll_(0) {};
    Player(string name) : name_(name), bankroll_(0) {};

    const int getBankroll() { return bankroll_; }
    const string getPlayerName() { return name_; }

    //const string printHand();
    //const string printScore();

    //void drawCard(shared_ptr<Card>, bool = false);
    void deposit(int bankroll) { bankroll_ = bankroll; }
    void bet(int bet) { bankroll_ -= bet; }
    void doubleDown(int bet) { bankroll_ -= bet; }
    void win(int win) { bankroll_ += win; }

    //void doubleDown(shared_ptr<Card>, bool = false);
    //void hit(shared_ptr<Card>, bool = false);
    //void split(bool = false);
    //void stand(bool = false);
};

#endif