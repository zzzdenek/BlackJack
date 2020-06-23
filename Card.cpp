// Card.cpp
// Author: Zdenek Zeman
// Last change: 15-7-18

#include "Card.h"

#include <sstream>

using std::stringstream;

Card::Card(Value value, Suit suit) : suit_(suit), value_(value)
{
    switch (value_)
    {
    case TWO:
        score_ = 2;
        break;
    case THREE:
        score_ = 3;
        break;
    case FOUR:
        score_ = 4;
        break;
    case FIVE:
        score_ = 5;
        break;
    case SIX:
        score_ = 6;
        break;
    case SEVEN:
        score_ = 7;
        break;
    case EIGHT:
        score_ = 8;
        break;
    case NINE:
        score_ = 9;
        break;
    case ACE:
        score_ = 11;
        break;
    default:
        score_ = 10;
        break;
    }
}

const string Card::getSuit()
{
    switch (suit_)
    {
    case CLUBS:
        return "c";
    case DIAMONDS:
        return "d";
    case HEARTS:
        return "h";
    case SPADES:
        return "s";
    default:
        return "x";
    }
}

const string Card::getValue()
{
    switch (value_)
    {
    case TWO:
        return "2";
    case THREE:
        return "3";
    case FOUR:
        return "4";
    case FIVE:
        return "5";
    case SIX:
        return "6";
    case SEVEN:
        return "7";
    case EIGHT:
        return "8";
    case NINE:
        return "9";
    case TEN:
        return "T";
    case JACK:
        return "J";
    case QUEEN:
        return "Q";
    case KING:
        return "K";
    case ACE:
        return "A";
    default:
        return "X";
    }
}

const string Card::printCard()
{
    stringstream stream;
    stream << "| " << getValue() << getSuit() << " |";
    string print;
    print = stream.str();
    return print;
}

const Card::Suit Card::getNextSuit(Suit suit)
{
    switch (suit)
    {
    case CLUBS:
        return DIAMONDS;
    case DIAMONDS:
        return HEARTS;
    case HEARTS:
        return SPADES;
    case SPADES:
        return NO_SUIT;
    case NO_SUIT:
        return NO_SUIT;
    }
    return NO_SUIT;
}

const Card::Value Card::getNextValue(Value value)
{
    switch (value)
    {
    case TWO:
        return THREE;
    case THREE:
        return FOUR;
    case FOUR:
        return FIVE;
    case FIVE:
        return SIX;
    case SIX:
        return SEVEN;
    case SEVEN:
        return EIGHT;
    case EIGHT:
        return NINE;
    case NINE:
        return TEN;
    case TEN:
        return JACK;
    case JACK:
        return QUEEN;
    case QUEEN:
        return KING;
    case KING:
        return ACE;
    case ACE:
        return NO_VALUE;
    case NO_VALUE:
        return NO_VALUE;
    }
    return NO_VALUE;
}