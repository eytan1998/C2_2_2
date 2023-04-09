
#include "player.hpp"

#include <utility>


Player::Player(std::string name) : isInGame(false), handDeck(Deck()), takenDeck(Deck()), name(std::move(name)),
                                   round_num(0), round_won(0), draw_num(0) {}

void Player::enterGame() {
    this->isInGame = true;
}

void Player::endGame() {
    this->isInGame = false;
}

bool Player::isBusy() const {
    return this->isInGame;
}

std::string Player::getName() {
    return this->name;
}


//prints the amount of cards left. should be 26 but can be less if a draw was played
int Player::stacksize() {
    return this->handDeck.getCardsLeft();
}

// prints the amount of cards this player has won.
int Player::cardesTaken() {
    return this->takenDeck.getCardsLeft();
}

Card Player::topHandCard() {
    return this->handDeck.top();
}

void Player::popHandCard() {
    this->handDeck.pop();
}

void Player::getCardInStart(Card card) {
    this->handDeck.push(card);
}

void Player::wonCard(Card card) {
    this->takenDeck.push(card);
}


void Player::printStats() {
    std::cout << "========== " << this->name << " statistics: " << "==========" << std::endl
              << "Round played: " << this->round_num << std::endl
              << "Round won: " << this->round_won << std::endl
              << "Win rate: " << ((26 - stacksize() == 0) ? "didn't played" :
                                  std::to_string(100 * (round_won * 1.0 / round_num))) + "%" << std::endl
              << "Cards drawn: " << (26 - stacksize()) << std::endl
              << "Draw amount: " << this->draw_num << std::endl
              << "Draw rate: " << ((26 - stacksize() == 0) ? "didn't played" :
                                   std::to_string(100 * (draw_num * 1.0 / (26 - stacksize()) * 1.0))) + "%" << std::endl
              << "Cards won: " << this->cardesTaken() << std::endl;
}

void Player::reset() {
    this->round_num = 0;
    this->round_won = 0;
    this->draw_num = 0;
    this->handDeck.flush();
    this->takenDeck.flush();
}

void Player::wasDraw() {
    this->draw_num++;
}

void Player::playerWon() {
    this->round_won++;
}

void Player::roundPlayed() {
    this->round_num++;

}

