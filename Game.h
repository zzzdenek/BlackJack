// Game.h
// Author: Zdenek Zeman
// Last change: 21-7-18

#ifndef GAME_H
#define GAME_H

#include "Deck.h"
#include "Card.h"
#include "Player.h"

#include <memory>
#include <string>


using std::shared_ptr;
using std::string;

class Game
{
private:
    Deck deck_;
    Box dealer_box_;
    shared_ptr <Box> player_box_;
    shared_ptr <Box> player_box_split_;
    Player dealer_;
    Player player_;
    int next_card_index_;
    bool action_finished_;
    bool split_flag_;
    bool first_action_flag_;
    string file_name_;
    string file_text_;

    Game(const Game &copy) {};

    void addToFileText(string);

public:
    Game();

    void printPlayerHand();
    void printPlayerResult();
    void printPlayerFirstHand();
    void printPlayerFirstHandResult();
    void printPlayerSecondHand();
    void printPlayerSecondHandResult();
    void printDealerHand();

    void deposit();
    void bettingRound();
    void play();
    void bet(int);
    void deal();
    //string getPossibleActions();
    void action(shared_ptr <Box>, bool);
    void doubleDown(shared_ptr <Box>);
    void hit(shared_ptr <Box> box)
        { box->drawCard(deck_[next_card_index_--]); }
    void stand();
    void split();
    void printGame();
    void printInfo();
    void dealer_action();
    void evaluateResult(shared_ptr <Box>);
    void executeResult(shared_ptr <Box>);
    void output();
};

#endif