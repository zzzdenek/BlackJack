// Deck.h
// Author: Zdenek Zeman
// Last change: 15-7-18

#ifndef DECK_H
#define DECK_H

#include "Card.h"

#include <vector>
#include <memory>

using std::vector;
using std::shared_ptr;

class Deck
{
private:
    vector<shared_ptr<Card>> deck_;

    
    
    Deck(const Deck &copy) {};

public:
    Deck() {};
    Deck(int);

    const unsigned int getDeckSize() { return deck_.size(); }
    const string printDeckCard(int index)
        { return deck_[index]->printCard(); }
    //const int getCardScore(int index) { return deck_[index]->getScore(); }

    const shared_ptr<Card> operator[](const int index)
        { return deck_[index]; }
    const shared_ptr<Card> back()
        { return deck_.back(); }
    void push_back (const shared_ptr<Card> card)
        { deck_.push_back(card); }
    
    void shuffle();
    void createDeck();
    void popDeck() { deck_.pop_back(); }

};

#endif