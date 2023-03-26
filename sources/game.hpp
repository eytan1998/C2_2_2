
#ifndef GAME_H
#define GAME_H
#include <utility>

class Game {
    Player * player1;
    Player * player2;
    stack<string> turns;

public:
    Game(Player &player1, Player &player2){
        this->player1 = &player1;
        this->player2 = &player2;

//        if (player1 == player2){
//            throw std::invalid_argument("player cant play against himself");
//        }
            //cant play to games parallel
            if (this->player1->isBusy() || this->player2->isBusy()) {
                throw std::invalid_argument("One or more of player is in ather game");
            }


            //for not to games
            this->player1->enterGame();
            this->player2->enterGame();
            //make sure dont have from last game
            this->player1->resetCards();
            this->player2->resetCards();

            Deck gameDeck = Deck::makeCompleteDeck();
            //spread shuffle deck evenly
            while (!gameDeck.isEmpty()) {
                this->player1->getCardInStart(gameDeck.top());
                gameDeck.pop();
                this->player2->getCardInStart(gameDeck.top());
                gameDeck.pop();
            }



    }

    void playTurn() {
        if (player1->stacksize() == 0 || player2->stacksize() == 0
            || !player1->isBusy() || !player2->isBusy())
            throw std::logic_error("One or more of the player not playing");


        Card c1 = player1->topHandCard();
        Card c2 = player2->topHandCard();
        string turnLog = player1->getName() + " played " + c1.toString() + " "
                         + player2->getName() + " played " + c2.toString() + ". ";

        int whoWin = Card::whoWin(c1, c2);
        if (whoWin == 1) {//player 1 win
            //remove from hand
            player1->popHandCard();
            player2->popHandCard();
            //move to discard pile
            player1->wonCard(c1);
            player1->wonCard(c2);

            turnLog.append(player1->getName() + " Wins.");

        } else if (whoWin == 2) {//player 2 win
            //remove from hand
            player1->popHandCard();
            player2->popHandCard();
            //move to discard pile
            player2->wonCard(c2);
            player2->wonCard(c1);

            turnLog.append(player2->getName() + " Wins.");
        } else {//draw
            while (true) {
                turnLog.append(" Draw.");

                //remove from hand
                player1->popHandCard();
                player2->popHandCard();
                //update about draw
                player1->wasDraw();
                player2->wasDraw();

                if (player1->stacksize() == 0 || player2->stacksize() ==  0) {
                    //TODO return cards
                    break;
                }
                //
                break;

            }

        }
        if (player1->stacksize() == 0){
            player1->endGame();
            int winner = whoWinner();
            if (winner == 1) player1->playerWon();
            else player1->playerLost();
        }
        if (player2->stacksize() == 0){
            player2->endGame();
            int winner = whoWinner();
            if (winner == 2) player2->playerWon();
            else player2->playerLost();
        }
        //add the turn to the log
        turns.push(turnLog);


    }


    void playAll() {
        if (player1->stacksize() == 0 || player2->stacksize() == 0
            || !player1->isBusy() || !player2->isBusy())
            throw std::logic_error("One or more of the player not playing");

        while (true) {
            try {
                playTurn();

            } catch (const std::logic_error & e) {
                break;
            }
        }
        player1->endGame();
        player2->endGame();
    }

    void printLastTurn() {
        string lastTurn;
        if (turns.empty()) lastTurn = "Players didn't played";
        else lastTurn = turns.top();
        std::cout << lastTurn << endl;
    }

    int whoWinner(){
        if (player1->cardesTaken() > player2->cardesTaken())return 1;
        if (player1->cardesTaken() < player2->cardesTaken())return 2;
        return 0;
    }
    void printWiner() {
        int winner = whoWinner();
        switch (winner) {
            case 0:
                std::cout << "Draw" << endl;
                break;
            case 1:
                std::cout << player1->getName() << endl;
                break;
            case 2:
                std::cout << player2->getName() << endl;
                break;
            default:
                break;
        }
    }

    void printLog() {
        stack<string> temp;
        while (!turns.empty()) {
            temp.push(turns.top());
            turns.pop();
        }
        int index = 1;
        while (!temp.empty()) {
            std::cout <<"Turn #"<<index++<<": " << temp.top() << endl;
            turns.push(temp.top());
            temp.pop();
        }

    }

    void printStats() {
        player1->printStats();
        player2->printStats();
    }
};
#endif
