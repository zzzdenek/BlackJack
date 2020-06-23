// Player.cpp
// Author: Zdenek Zeman
// Last change: 18-7-18

#include "Player.h"

#include <sstream>
#include <memory>

using std::stringstream;
using std::shared_ptr;
/*
const string Player::printHand()
{
    string string;
    stringstream stream;

    if (box_->getBet() == 0)
    {
        stream << box_->printHand();
    }
    else if (box_split_->getActive())
    {
        stream << "$" << box_->getBet() << " " << box_->printHand() <<
            " second Hand: " << "$" << box_split_->getBet() << " " <<
            box_split_->printHand();
        string  = stream.str();
        stream.str("");
    }
    else
    {
        stream << "$" << box_->getBet() << " " << box_->printHand();
        string = stream.str();
        stream.str("");
    }
    return string;
}

const string Player::printScore()
{
    string string;
    if (box_split_->getActive())
    {
        stringstream stream;
        stream << box_->printScore() << " second Hand: " <<
            box_split_->printHand();
        string  = stream.str();
        stream.str("");
    }
    else
    {
        string = box_->printScore();
    }
    return string;
}

void Player::drawCard(shared_ptr<Card> card,
    bool second_box)
{
    if (second_box)
    {
        box_split_->drawCard(card);
    }
    else
    {
        box_->drawCard(card);
    }
}

void Player::doubleDown(shared_ptr<Card> card,
    bool second_box)
{
    
    shared_ptr<Box> box_ptr (new Box);
    if (second_box)
    {
        box_ptr = box_split_;
    }
    else
    {
        box_ptr = box_;
    }
    bankroll_ -= box_ptr->getBet();
    box_ptr->doubleDown();
    drawCard(card);
}

void Player::hit(shared_ptr<Card> card, bool second_box)
{
    
}*/