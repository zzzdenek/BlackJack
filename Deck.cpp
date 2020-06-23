// Game.cpp
// Author: Zdenek Zeman
// Last change: 15-7-18

#include "Deck.h"

#include <algorithm>
//#include <chrono>
#include <memory>
//#include <fstream>
//#include <cstdlib>
#include <random>
//#include <iterator>

using std::shared_ptr;

void Deck::createDeck()
{
    Card card;
    Card::Suit suit = Card::CLUBS;
    Card::Value value = Card::TWO;

    for (bool suit_flag = true; suit_flag;)
    {
        value = Card::TWO;
        for (bool value_flag = true; value_flag;)
        {
            shared_ptr<Card> ptr (new Card(value, suit));
            deck_.push_back(ptr);
            value = card.getNextValue(value);
            if (value == Card::NO_VALUE) value_flag = false;
        }
        suit = card.getNextSuit(suit);
        if (suit == Card::NO_SUIT) suit_flag = false;
    }
}

Deck::Deck(int number_decks)
{
    for (int counter = 0; counter < number_decks;
        counter++)
    {
        createDeck();
    }
    shuffle();
}
/*
int read_urandom()
{
    union {
		int value;
		char cs[sizeof(int)];
	} u;

	std::ifstream rfin("/dev/urandom");
	rfin.read(u.cs, sizeof(u.cs));
	rfin.close();

	return u.value;
}*/

void Deck::shuffle()
{
    /*unsigned seed = std::chrono::system_clock::now().
        time_since_epoch().count();
    std::default_random_engine e(seed);*/
    //std::shuffle(deck_.begin(), deck_.end(), read_urandom());
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(deck_.begin(), deck_.end(), g);
}