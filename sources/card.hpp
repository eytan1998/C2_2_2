
#ifndef CARD_H
#define CARD_H
#include <iostream>

class Card {
//    Jack = 11, Queen = 12, King = 13, Ace = 14
    int value;
    //    Hearts = 0, Spades = 1, Clubs = 2, Diamonds = 3
    int sign;

public:
    Card(int value, int sign);
    std::string toString() const;
    static int whoWin(Card card1, Card card2);
};

#endif