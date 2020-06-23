// Box.cpp
// Author: Zdenek Zeman
// Last change: 18-7-18

#include "Box.h"

#include <sstream>

using std::stringstream;

const string Box::printHand()
{
    stringstream stream;
    if (!dealer_)
    {
        stream << "$" << bet_ << " ";
    }
    for (unsigned int counter = 0;
        counter < hand_.getDeckSize(); counter++)
    {
        stream << hand_.printDeckCard(counter);
    }
    string string = stream.str();
    stream.str("");
    return string;
}

const string Box::printScore()
{
    stringstream stream;
    if ( (score_ == 21) & (hand_.getDeckSize() == 2) )
    {
        stream << "BLACK JACK";
    }
    else
    {
        stream << score_;
        if (ace_)
        {
            if (score_ < 21)
            {
                stream << "/" << score_ - 10;
            }
        }
        if (score_ > 21)
        {
            stream << " BUST";
        }
    }
    string string = stream.str();
    stream.str("");
    return string;
}

void Box::drawCard(shared_ptr<Card> card)
{ 
    hand_.push_back(card);
    if (!ace_)
    {
        if (card->getValue() == "A")
        {
            ace_ = true;
        }
    }
    score_ += card->getScore();
    if (ace_)
    {
        if (score_ > 21)
        {
            score_ -= 10;
            ace_ = false;
        }
    }
}

void Box::split()
{
    score_ -= hand_[getSize() - 1]->getScore();
    if (hand_[getSize() - 1]->getScore() == 11)
    {
        score_ += 10;
    }
    hand_.popDeck();
}

bool Box::getBlackJack()
{
    if ( (getSize() == 2) & (getScore() == 21) )
    {
        return true;
    }
    else
    {
        return false;
    }
}