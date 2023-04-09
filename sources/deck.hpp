
#ifndef DECK_H
#define DECK_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

#include <stack>
#include "card.hpp"



class Deck {
    std::stack<Card> deck;

public:
    //default constractor

    int getCardsLeft();

    Card top();

    void pop();

    void push(Card card);

    bool isEmpty();

    void flush();

    static Deck makeCompleteDeck();
};

#endif