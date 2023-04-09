#ifndef PLAYER_H
#define PLAYER_H

#include "deck.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
namespace ariel{}//make compiler happy
class Player {
    std::string name;
    bool isInGame;

    Deck handDeck;
    Deck takenDeck;

    //for stats
    int round_num;
    int round_won;
    int draw_num;
public:

    explicit Player(std::string name);

    void enterGame();

    void endGame();

    bool isBusy() const;

    std::string getName();


//prints the amount of cards left. should be 26 but can be less if a draw was played
    int stacksize();

    // prints the amount of cards this player has won.
    int cardesTaken();

    Card topHandCard();

    void popHandCard();

    void getCardInStart(Card card);

    void wonCard(Card card);

    void wasDraw();

    void playerWon();

    void printStats();

    void reset();

    void roundPlayed();
};

#endif