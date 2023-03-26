
#ifndef DECK_H
#define DECK_H

#include <stack>

using namespace std;

class Deck {
    std::stack<Card> deck;

public:
    //default constractor

    int getCardsLeft() {
        return (int) this->deck.size();
    }

    Card top() {
        return deck.top();
    }

    void pop() {
        deck.pop();
    }

    void push(Card c) {
        deck.push(c);
    }

    bool isEmpty() {
        return deck.empty();
    }

    void flush() {
        while (!deck.empty()) {
            deck.pop();
        }
    }

    static Deck makeCompleteDeck() {
        // Array from 0 to 51
        int a[] = {0, 1, 2, 3, 4, 5, 6, 7, 8,
                   9, 10, 11, 12, 13, 14, 15,
                   16, 17, 18, 19, 20, 21, 22,
                   23, 24, 25, 26, 27, 28, 29,
                   30, 31, 32, 33, 34, 35, 36,
                   37, 38, 39, 40, 41, 42, 43,
                   44, 45, 46, 47, 48, 49, 50,
                   51};

        //shuffle
        // Initialize seed randomly
        srand(time(nullptr));
        for (int i = 0; i < 52; i++) {
            // Random for remaining positions.
            int r = i + (rand() % (52 - i));
            swap(a[i], a[r]);
        }
        Deck d = Deck();
        for (int temp : a) {
            temp += 8;//to start from 2, 8/4=2, 8%4=0
            d.push(Card(temp / 4, temp % 4));
        }
        return d;
    }
};

#endif