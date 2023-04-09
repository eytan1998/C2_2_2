
#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <stdexcept>
#include "player.hpp"

class Game {
    Player &player1;
    Player &player2;
    std::stack<std::string> turns;
    //decks to give after the draw
    Deck p1_pit = Deck();
    Deck p2_pit = Deck();
    std::string turnLog;

public:
    Game(Player &player1, Player &player2);

    void playTurn();


    void playAll();

    void endGame();

    void printLastTurn();

    int whoWinner();

    void printWiner();

    void printLog();

    void printStats();
};

#endif

