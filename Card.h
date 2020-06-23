// Card.h
// Author: Zdenek Zeman
// Last change: 5-7-18

#ifndef CARD_H
#define CARD_H

#include <string>

using std::string;

class Card
{
public:
    enum Suit
    {
        CLUBS,
        DIAMONDS,
        HEARTS,
        SPADES,
        NO_SUIT
    };

    enum Value
    {
        TWO,
        THREE,
        FOUR,
        FIVE,
        SIX,
        SEVEN,
        EIGHT,
        NINE,
        TEN,
        JACK,
        QUEEN,
        KING,
        ACE,
        NO_VALUE
    };

private:
    int score_;
    Suit suit_;
    Value value_;

public:
    Card() {};
    Card(Value, Suit);
    Card(const Card &copy) : score_(copy.score_),
        suit_(copy.suit_), value_(copy.value_) {};
    ~Card() {};

    const int getScore() { return score_; }
    const string getSuit();
    const string getValue();
    const string printCard();

    const Suit getNextSuit(Suit);
    const Value getNextValue(Value);

};
#endif