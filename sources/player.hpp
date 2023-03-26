#ifndef PLAYER_H
#define PLAYER_H

#include <utility>
#include "deck.hpp"

class Player {
    string name;
    bool isInGame;

    Deck handDeck;
    Deck takenDeck;

    int games_win;
    int games_played;

    int card_draw;
    int draw;
public:

    explicit Player(string name) {
        isInGame = false;
        this->handDeck = Deck();
        this->takenDeck = Deck();
        this->name = std::move(name);

        games_win =0;
        games_played =0;
        card_draw =0;
        draw =0;
    }

    void enterGame(){
        isInGame = true;
    }
    void endGame(){
        isInGame = false;
    }
    bool isBusy(){
        return isInGame;
    }
    string getName() {
        return name;
    }


//prints the amount of cards left. should be 26 but can be less if a draw was played
    int stacksize() {
        return this->handDeck.getCardsLeft();
    }

    // prints the amount of cards this player has won.
    int cardesTaken() {
        return this->takenDeck.getCardsLeft();
    }

    Card topHandCard() {
        return handDeck.top();
    }

    void popHandCard() {
        handDeck.pop();
        card_draw++;
    }

    void getCardInStart(Card c) {
        handDeck.push(c);
    }

    void wonCard(Card c) {
        takenDeck.push(c);
    }

    void wasDraw() {
        draw++;
    }

    void playerWon() {
        this->games_win++;
        this->games_played++;
    }

    void playerLost() {
        this->games_played++;
    }

    void printStats() {
        std::cout <<"========== "<< this->name << " statistics: " <<"=========="<< endl
                  << "Games played: " << this->games_played << endl
                  << "Win rate: " << ((this->games_played == 0) ? "didn't played" : std::to_string(100*(games_win*1.0/games_played )))+"%"<< endl
                  << "Cards won: " << this->cardesTaken() << endl
                  << "Draw rate: " << ((this->card_draw == 0) ? "didn't played" : std::to_string(100*(draw*1.0/card_draw*1.0 )))+"%"<< endl
                  << "Draw amount: " << this->draw << endl
                  << "Cards drawn: " << this->card_draw << endl;
    }

    void resetCards() {
        handDeck.flush();
        takenDeck.flush();
    }
};
#endif