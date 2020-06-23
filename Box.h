// Box.h
// Author: Zdenek Zeman
// Last change: 18-7-18

#ifndef BOX_H
#define BOX_H

#include "Deck.h"

#include <string>
#include <memory>

using std::string;
using std::shared_ptr;

class Box
{
public:
    enum Result
    {
        WIN,
        TIE,
        LOSS,
        BLACKJACK
    };

private:
    int bet_;
    int score_;

    Deck hand_;
    
    bool ace_;
    bool dealer_;
    bool active_;

    Result result_;

    Box(const Box &copy) {};

public:
    //Box() {};
    Box(bool dealer = false, bool active = true) : bet_(0),
        score_(0), hand_(0),ace_(false), dealer_(dealer),
        active_(active) {};
    
    void setDealer(bool dealer) { dealer_ = dealer; }
    void setActive() { active_ = true; }
    void setResult(Result result) { result_ = result; }
    
    bool getActive() { return active_; }
    const int getBet() { return bet_; }
    const int getScore() { return score_; }
    const int getCardValue(int index) { return hand_[index]->getScore(); }
    const int getSize() { return hand_.getDeckSize(); }
    bool getBlackJack();
    Result getResult() { return result_; }

    const string printHand();
    const string printScore();

    void drawCard(shared_ptr<Card>);
    void bet(int bet) { bet_ = bet; }
    void doubleDown() { bet_ += bet_; }
    void split();
    
};
#endif