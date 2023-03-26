
#ifndef CARD_H
#define CARD_H

class Card {
//    Jack = 11, Queen = 12, King = 13, Ace = 14
    int value;
    //    Hearts = 0, Spades = 1, Clubs = 2, Diamonds = 3
    int sign;

public:
    Card(int value, int sign) {
        if (value < 2 || value > 14) return;
        if (sign < 0 || sign > 3) return;
        this->value = value;
        this->sign = sign;
    }


    static int whoWin(Card card1, Card card2) {
        if ((card1.value > card2.value) || (card1.value == 2 and card2.value == 14))return 1;//first win
        if ((card1.value < card2.value) || (card2.value == 2 and card1.value == 14))return 2;//second win
        return 0;//draw
    }

    string toString() {
        string Svalue;
        string Ssign;
        //    Jack = 11, Queen = 12, King = 13, Ace = 14

        switch (this->value) {
            case 11:
                Svalue = "Jack";
                break;
            case 12:
                Svalue = "Queen";
                break;
            case 13:
                Svalue = "King";
                break;
            case 14:
                Svalue = "Ace";
                break;
            default:
                Svalue = std::to_string(this->value);
                break;
        }
        //    Hearts = 0, Spades = 1, Clubs = 2, Diamonds = 3

        switch (this->sign) {
            case 0:
                Ssign = "Hearts";
                break;
            case 1:
                Ssign = "Spades";
                break;
            case 2:
                Ssign = "Clubs";
                break;
            case 3:
                Ssign = "Diamonds";
                break;
        }
        return Svalue + " of " + Ssign;

    }

};

#endif