// Game.cpp
// Author: Zdenek Zeman
// Last change: 22-7-18

#include "Game.h"

#include <iostream>
#include <memory>
#include <fstream>
#include <sstream>

using std::cout;
using std::endl;
using std::cin;
using std::shared_ptr;
using std::stringstream;

string convert(int number)
{
    stringstream stream;
    if (number < 10)
    {
        stream << "0" << number;
    }
    else
    {
        stream << number;
    }
    return stream.str();
}

Game::Game() : deck_(6), dealer_box_(true), player_box_(new Box()),
    player_box_split_(new Box(false, false)), dealer_("Dealer"),
    player_(), next_card_index_(deck_.getDeckSize() - 1),
    action_finished_(false), split_flag_(false),
    first_action_flag_(false), file_name_(), file_text_()
{
    time_t now = time(0);
    tm *local_time = localtime(&now);

    int year = 1900 + local_time->tm_year;
    stringstream year_stream;
    year_stream << year;

    int month = 1 + local_time->tm_mon;
    int day = local_time->tm_mday;
    int hour = local_time->tm_hour;
    int minute = local_time->tm_min;
    int second = local_time->tm_sec;

    stringstream stream;

    stream << year_stream.str() << "-" << convert(month) << "-"
        << convert(day) << "_" << convert(hour) << ":"
        << convert(minute) << ":" << convert(second) << std::endl;
    
    file_name_ = stream.str();
}

void Game::addToFileText(string string)
{
    stringstream text;
    text.str(file_text_);
    text << string;
    file_text_ = text.str();
}

void Game::printPlayerHand()
{
    cout << "Players hand: " << player_box_->printHand() << endl;
    cout << "Players score: " << player_box_->printScore() << endl;
}

void Game::printPlayerResult()
{
    cout << "Player ";
    switch (player_box_->getResult())
    {
        case Box::WIN:
            cout << "won $" << player_box_->getBet() * 2 << "!" << endl;
            break;
        case Box::TIE:
            cout << "won $" << player_box_->getBet() << "!" << endl;
            break;
        case Box::LOSS:
            cout << "lost his bet $" << player_box_->getBet() << "!" << endl;
            break;
        case Box::BLACKJACK:
            cout << "won $" <<
                player_box_->getBet() * 2 + player_box_->getBet() / 2
                << "!" << endl;
            break;
    }
}

void Game::printPlayerFirstHand()
{
    cout << "Players first hand: " << player_box_->printHand() << endl;
    cout << "Players first hand score: " << player_box_->printScore() << endl;
}

void Game::printPlayerFirstHandResult()
{
    cout << "Player ";
    switch (player_box_->getResult())
    {
        case Box::WIN:
            cout << "won $" << player_box_->getBet() * 2 << " on his 1st hand!"
                << endl;
            break;
        case Box::TIE:
            cout << "won $" << player_box_->getBet() << " on his 1st hand!"
                << endl;
            break;
        case Box::LOSS:
            cout << "lost his bet $" << player_box_->getBet()
                << " on his 1st hand!" << endl;
            break;
        case Box::BLACKJACK:
            cout << "won $" <<
                player_box_->getBet() * 2 + player_box_->getBet() / 2
                << "!" << endl;
            break;
    }
}

void Game::printPlayerSecondHand()
{
    cout << "Players 2nd hand: " << player_box_split_->printHand() << endl;
    cout << "Players 2nd hand score: " << player_box_split_->printScore()
        << endl;
}

void Game::printPlayerSecondHandResult()
{
    cout << "Player ";
    switch (player_box_split_->getResult())
    {
        case Box::WIN:
            cout << "won $" << player_box_split_->getBet() * 2
                << " on his 2nd hand!" << endl;
            break;
        case Box::TIE:
            cout << "won $" << player_box_split_->getBet()
                << " on his 2nd hand!" << endl;
            break;
        case Box::LOSS:
            cout << "lost his bet $" << player_box_split_->getBet()
                << " on his 2nd hand!" << endl;
            break;
        case Box::BLACKJACK:
            cout << "won $" <<
                player_box_->getBet() * 2 + player_box_->getBet() / 2
                << "!" << endl;
            break;
    }
}

void Game::printDealerHand()
{
    cout << "Dealers hand: " << dealer_box_.printHand() << endl;
    cout << "Dealers score: " << dealer_box_.printScore() << endl;
}

void Game::deposit()
{
    cout << file_name_;
    int bankroll;
    cout << "Deposit please!" << endl << "$";
    cin >> bankroll;
    player_.deposit(bankroll);
    cout << "Thank you!" << endl;
    
}

void Game::bettingRound()
{
    int bet;
    cout << "Your bankroll: $" << player_.getBankroll() << endl <<
        "Place your bet please!" << endl << "$";
    cin >> bet;

    stringstream stream;
    stream << "Player bets $" << bet << "." << endl;
    addToFileText(stream.str());

    Game::bet(bet);
    cout << "Thank you! Good Luck!" << endl;
}

void Game::play()
{
    deck_.shuffle();
    deal();
    printGame();
    //shared_ptr<Box> box_ptr (new Box());
    //box_ptr = player_box_;
    while ( (player_box_->getScore() < 21) & (!action_finished_) )
    {
        action(player_box_, false);
        if ( player_box_split_->getActive() )
        {
            printPlayerFirstHand();
        }
        else
        {
            printPlayerHand();
        }
    }
    if ( player_box_split_->getActive() )
    {
        action_finished_ = false;
        printPlayerSecondHand();
        while ( (player_box_split_->getScore() < 21) & (!action_finished_) )
        {
            action(player_box_split_, true);
            printPlayerSecondHand();
        }
    }
    //printGame();
    bool dealer_flag = true;
    if ( player_box_split_->getActive() )
    {
        if ( (player_box_->getScore() > 21)
            & (player_box_split_->getScore() > 21) )
        {
            dealer_flag = false;
        }
    }
    else
    {
        if ( (player_box_->getScore()) > 21 )
        {
            dealer_flag = false;
        }
    }
    if (dealer_flag)
    {
        cout << "It's dealer's turn!" << endl;
        dealer_action();
        printGame();
    }
    
    evaluateResult(player_box_);
    executeResult(player_box_);
    if ( (player_box_split_->getActive()) )
    {
        evaluateResult(player_box_split_);
        executeResult(player_box_split_);
        printPlayerFirstHandResult();
        printPlayerSecondHandResult();
    }
    else
    {
        printPlayerResult();
    }
    cout << "Your bankroll $" << player_.getBankroll() << endl;
}

void Game::bet(int bet)
{
    player_.bet(bet);
    player_box_->bet(bet);
}

void Game::printGame()
{
    printDealerHand();
    if (player_box_split_->getActive())
    {
        printPlayerFirstHand();
        printPlayerSecondHand();
    }
    else
    {
        printPlayerHand();        
    }
}

void Game::deal()
{
    player_box_->drawCard(deck_[next_card_index_--]);
    dealer_box_.drawCard(deck_[next_card_index_--]);
    player_box_->drawCard(deck_[next_card_index_--]);
}

void Game::action(shared_ptr <Box> box, bool second_hand)
{
    enum Action
    {
        DOUBLE,
        HIT,
        STAND,
        SPLIT
    };
    
    Action action;
    string input;
    bool input_flag = false;
    bool split_possible = false;
    do
    {
        input_flag = false;
        cout << "Your possible actions:" << endl;
        if (!first_action_flag_)
        {
            cout << "[D]ouble # ";
        }
        cout << "[H]it # [S]tand";
        if ( (box->getCardValue(0) == box->getCardValue(1))
            & (!split_flag_) )
        {
            cout << " # [X]Split";
            split_possible = true;
        }
        cout << endl;
        cout << "Your decision";
        if (second_hand)
        {
            cout << " for your 2nd hand";
        }
        else if (player_box_split_->getActive())
        {
            cout << " for your 1st hand";
        }
        cout << "?" << endl;
        cin >> input;
        cout << "You decided to ";
        if ( ((input == "d") | (input == "D")) & (!first_action_flag_) )
        {
            cout << "DOUBLE DOWN";
            action = DOUBLE;
        }
        else if ( (input == "h") | (input == "H") )
        {
            cout << "HIT";
            action = HIT;
        }
        else if ( (input == "s") | (input == "S") )
        {
            cout << "STAND";
            action = STAND;
        }
        else if ( split_possible & ( (input == "x") | (input == "X") ) )
        {
            cout << "SPLIT";
            action = SPLIT;
        }
        else
        {
            cout << "INPUT ERROR!" << endl;
            input_flag = true;
        }
        if (!input_flag)
        {
            cout << "!" << endl;
        }
    }
    while (input_flag);

    first_action_flag_ = true;

    switch (action)
    {
        case DOUBLE:
            doubleDown(box);
            break;
        case HIT:
            hit(box);
            break;
        case STAND:
            stand();
            break;
        case SPLIT:
            split();
            break;
    }
}

void Game::doubleDown(shared_ptr <Box> box)
{
    player_.doubleDown(box->getBet());
    box->doubleDown();
    box->drawCard(deck_[next_card_index_--]);
    action_finished_ = true;
}

void Game::split()
{
    split_flag_ = true;
    first_action_flag_ = false;
    player_box_split_->setActive();
    player_.bet(player_box_->getBet());
    player_box_split_->bet(player_box_->getBet());
    player_box_->split();
    player_box_split_->drawCard(deck_[next_card_index_ + 1]);
    player_box_->drawCard(deck_[next_card_index_--]);
    player_box_split_->drawCard(deck_[next_card_index_--]);
    printPlayerFirstHand();
    printPlayerSecondHand();
}

void Game::stand()
{
    action_finished_ = true;
}

void Game::dealer_action()
{
    while ( (dealer_box_.getScore() < 17) )
    {
        
        printDealerHand();
        cout << "Dealer draws..." << endl;
        dealer_box_.drawCard(deck_[next_card_index_--]);
    }
}

void Game::evaluateResult(shared_ptr <Box> box)
{
    if ( (box->getScore() > 21) )
    {
        box->setResult(Box::LOSS);
    }
    else if ( (dealer_box_.getScore() > 21) )
    {
        box->setResult(Box::WIN);
    }
    else if ( (box->getBlackJack()))
    {
        if ( (dealer_box_.getBlackJack()) )
        {
            box->setResult(Box::TIE);
        }
        else
        {
            box->setResult(Box::BLACKJACK);
        }
    }
    else if ( (dealer_box_.getBlackJack()) )
    {
        box->setResult(Box::LOSS);
    }
    else if ( ( (box->getScore()) > (dealer_box_.getScore()) ) )
    {
        box->setResult(Box::WIN);
    }
    else if ( ( (box->getScore()) == (dealer_box_.getScore()) ) )
    {
        box->setResult(Box::TIE);
    }
    else
    {
        box->setResult(Box::LOSS);
    }
}

void Game::executeResult(shared_ptr <Box> box)
{
    switch (box->getResult())
    {
        case Box::WIN:
            player_.win(box->getBet() * 2);
            break;
        case Box::TIE:
            player_.win(box->getBet());
            break;
        case Box::LOSS:
            break;
        case Box::BLACKJACK:
            player_.win(box->getBet() * 2 + box->getBet() / 2);
            break;
    }
}

void Game::printInfo()
{
    //cout << "Players name: " << player_.getPlayerName() << endl;
    //cout << "Size of deck = " << deck_.getDeckSize() << endl;
    cout << "card[311] " << deck_[311]->printCard() << endl;
    cout << "card[312] " << deck_[310]->printCard() << endl;
    cout << "card[313] " << deck_[309]->printCard() << endl;
    cout << "next_card_index_ = " << next_card_index_ << endl;
    cout << "dealers hand: " << dealer_box_.printHand() << endl;
    cout << "players hand: " << player_box_->printHand() << endl;
}

void Game::output()
{
    //std::ofstream outfile("")
}