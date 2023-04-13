
#include "game.hpp"


Game::Game(Player &player1, Player &player2) : player1(player1), player2(player2) {

    //cant play to games parallel
    if (this->player1.isBusy() || this->player2.isBusy()) {
        throw std::invalid_argument("One or more of player is in ather game");
    }

    //change player if wont throw exception
    if (&player1 != &player2) {
        //for not to games
        this->player1.enterGame();
        this->player2.enterGame();
        //make sure dont have from last game
        this->player1.reset();
        this->player2.reset();

        Deck gameDeck = Deck::makeCompleteDeck();
        //spread shuffle deck evenly
        while (!gameDeck.isEmpty()) {
            this->player1.getCardInStart(gameDeck.top());
            gameDeck.pop();
            this->player2.getCardInStart(gameDeck.top());
            gameDeck.pop();
        }
    }

}

void Game::playTurn() {
    //cant play against himself
    if (&player1 == &player2) {
        throw std::invalid_argument("player cant play against himself");
    }
    if (player1.stacksize() == 0 || player2.stacksize() == 0
        || !player1.isBusy() || !player2.isBusy()) {
        throw std::logic_error("One or more of the player not playing");
    }

    //only if not if middle of draw
    if (p1_pit.isEmpty() && p2_pit.isEmpty()) {
        player1.roundPlayed();
        player2.roundPlayed();
    }

    Card c1 = player1.topHandCard();
    Card c2 = player2.topHandCard();
    //remove from hands
    player1.popHandCard();
    player2.popHandCard();

    turnLog.append(player1.getName() + " played " + c1.toString() + " "
                   + player2.getName() + " played " + c2.toString() + ". ");

    int whoWin = Card::whoWin(c1, c2);
    if (whoWin == 1) {//player 1 win

        //if won draw
        while (!p1_pit.isEmpty()) {
            player1.wonCard(p1_pit.top());
            p1_pit.pop();
        }
        while (!p2_pit.isEmpty()) {
            player1.wonCard(p2_pit.top());
            p2_pit.pop();
        }

        //move to discard pile
        player1.wonCard(c1);
        player1.wonCard(c2);


        player1.playerWon();
        turnLog.append(player1.getName() + " Wins.");

    } else if (whoWin == 2) {//player 2 win
        //if won draw
        while (!p1_pit.isEmpty()) {
            player2.wonCard(p1_pit.top());
            p1_pit.pop();
        }
        while (!p2_pit.isEmpty()) {
            player2.wonCard(p2_pit.top());
            p2_pit.pop();
        }

        //move to discard pile
        player2.wonCard(c2);
        player2.wonCard(c1);

        player2.playerWon();
        turnLog.append(player2.getName() + " Wins.");
    } else {//draw
        turnLog.append("Draw. ");


        //update about draw
        player1.wasDraw();
        player2.wasDraw();

        //add to there pits
        p1_pit.push(c1);
        p2_pit.push(c2);

        //check if ended, players get own pit
        if (player1.stacksize() == 0 || player2.stacksize() == 0) {
            while (!p1_pit.isEmpty()) {
                player1.wonCard(p1_pit.top());
                p1_pit.pop();
            }
            while (!p2_pit.isEmpty()) {
                player2.wonCard(p2_pit.top());
                p2_pit.pop();
            }
            turns.push(turnLog);
            endGame();
            return;
        }
        //else draw two upside down card
        p1_pit.push(player1.topHandCard());
        p2_pit.push(player2.topHandCard());
        //remove from hand
        player1.popHandCard();
        player2.popHandCard();


        //check if can draw more cards, players get own pit
        if (player1.stacksize() == 0 || player2.stacksize() == 0) {
            while (!p1_pit.isEmpty()) {
                player1.wonCard(p1_pit.top());
                p1_pit.pop();
            }
            while (!p2_pit.isEmpty()) {
                player2.wonCard(p2_pit.top());
                p2_pit.pop();
            }
            turns.push(turnLog);
            endGame();
            return;
        }

        playTurn();

    }

    //if no text can be for first iteration of draw
    if (turnLog == "") return;
    //add the turn to the log
    turns.push(turnLog);
    turnLog = "";

    //also check if try end game twice
    if (player1.stacksize() == 0 || player2.stacksize() == 0 && (!player1.isBusy() && !player2.isBusy())) endGame();


}

void Game::endGame() {
    player1.endGame();
    player2.endGame();
}

void Game::playAll() {
    //cant play against himself
    if (&player1 == &player2) {
        throw std::invalid_argument("player cant play against himself");
    }
    if (player1.stacksize() == 0 || player2.stacksize() == 0
        || !player1.isBusy() || !player2.isBusy())
        throw std::logic_error("One or more of the player not playing");

    while (true) {
        try {
            playTurn();

        } catch (const std::logic_error &e) {
            break;
        }//wont catch player against himself
    }
    player1.endGame();
    player2.endGame();
}

void Game::printLastTurn() {
//    if (turns.empty())
//        throw std::logic_error("No round to print");
    if (!turns.empty())
        std::cout << turns.top() << std::endl;
}

int Game::whoWinner() {
    if (player1.cardesTaken() > player2.cardesTaken())return 1;
    if (player1.cardesTaken() < player2.cardesTaken())return 2;
    return 0;
}

void Game::printWiner() {
//    if (player1.isBusy() && player2.isBusy())
//        throw std::logic_error("Game didn't ended");

    int winner = whoWinner();
    switch (winner) {
        case 0:
            std::cout << "Draw" << std::endl;
            break;
        case 1:
            std::cout << player1.getName() << std::endl;
            break;
        case 2:
            std::cout << player2.getName() << std::endl;
            break;
        default:
            throw std::invalid_argument(&"can get only 0, 1, 2 not"[winner]);
            break;
    }
}

void Game::printLog() {
//    if (turns.empty())
//        throw std::logic_error("No round to print");

    std::stack<std::string> temp;
    while (!turns.empty()) {
        temp.push(turns.top());
        turns.pop();
    }
    int index = 1;
    while (!temp.empty()) {
        std::cout << "Turn #" << index++ << ": " << temp.top() << std::endl;
        turns.push(temp.top());
        temp.pop();
    }
}

void Game::printStats() {
    player1.printStats();
    player2.printStats();
}
