#include "doctest.h"

#include <stdexcept>

#include "sources/player.hpp"
#include "sources/game.hpp"

TEST_CASE("Deck Size") {
    SUBCASE("Testing player initialize deck size = 26") {
        Player p1("Alice");
        Player p2("Bob");
        Game game(p1, p2);
        CHECK_EQ(p1.stacksize(), 26);
        CHECK_EQ(p2.stacksize(), 26);
    }
    SUBCASE("Testing player deck size throughout game") {
        Player p1("Alice");
        Player p2("Bob");
        Game game(p1, p2);
        game.playTurn();
        //could be less than 25 if draw happened
        CHECK_LE(p1.stacksize(), 25);
        CHECK_LE(p2.stacksize(), 25);

        for (int i = 0; i < 2; ++i) {
            //if game done with a lot of draws
            try {
                game.playTurn();
            } catch (...) { break; }
        }
        //could be less than 23 if draw happened
        CHECK_LE(p1.stacksize(), 23);
        CHECK_LE(p2.stacksize(), 23);
        try {
            game.playAll();
        } catch (...) {}
        //game end when both dont have cards in hand
        CHECK_EQ(p1.stacksize(), 0);
        CHECK_EQ(p2.stacksize(), 0);
    }
}

TEST_CASE("Card taken") {
    SUBCASE("Testing player initialize cards taken = 0") {
        Player p1("Alice");
        Player p2("Bob");
        Game game(p1, p2);
        //start with 0
        CHECK_EQ(p1.cardesTaken(), 0);
        CHECK_EQ(p2.cardesTaken(), 0);
    }
    SUBCASE("Testing player cards taken throughout game") {
        Player p1("Alice");
        Player p2("Bob");
        Game game(p1, p2);

        game.playTurn();
        //one of them have more than 0 , de-morgan
        CHECK(!(p1.cardesTaken() <= 0 && p2.cardesTaken() <= 0));
        CHECK_GT(p1.cardesTaken() + p2.cardesTaken(), 0);


        SUBCASE("also check cards taken always even") {
            //always get 2 cards -> had to be even
            //but can be odd if finish at middle of draw
            bool temp = p1.cardesTaken() % 2 == 0 || p1.stacksize() == 0;
            CHECK(temp);
            temp = p2.cardesTaken() % 2 == 0 || p2.stacksize() == 0;
            CHECK(temp);
        }

        //only if ended after one turn... (unlikely)
        try {
            game.playAll();
        } catch (...) {}

        SUBCASE("also check cards taken always even at the end") {

            //always get 2 cards -> has to be even
            //but can be odd if finish at middle of draw
            bool temp = p1.cardesTaken() % 2 == 0 || p1.stacksize() == 0;
            CHECK(temp);
            temp = p2.cardesTaken() % 2 == 0 || p2.stacksize() == 0;
            CHECK(temp);
        }

        //end with between 0 to 52
        CHECK_GE(p1.cardesTaken(), 0);
        CHECK_LE(p1.cardesTaken(), 52);
        CHECK_GE(p2.cardesTaken(), 0);
        CHECK_LE(p2.cardesTaken(), 52);
    }
}

TEST_CASE("Testing cards taken + deck size == 52") {
    Player p1("Alice");
    Player p2("Bob");
    Game game(p1, p2);
    game.playTurn();
    //check after one turn
    CHECK_EQ(p1.stacksize() + p2.stacksize() + p1.cardesTaken() + p2.cardesTaken(), 52);
    for (int i = 0; i < 2; ++i) {
        //if game done with a lot of draws
        try {
            game.playTurn();
        } catch (...) { break; }
    }
    SUBCASE("at the end") {

        //check after multiple turn
        CHECK_EQ(p1.stacksize() + p2.stacksize() + p1.cardesTaken() + p2.cardesTaken(), 52);
        //if game done with a lot of draws
        try {
            game.playAll();
        } catch (...) {}

        //check after all turn
        CHECK_EQ(p1.stacksize() + p2.stacksize() + p1.cardesTaken() + p2.cardesTaken(), 52);
    }

}

TEST_CASE("one player two games") {
    SUBCASE("Testing one player with two games -> trow exception") {
        Player p1("Alice");
        Player p2("Bob");
        Player p3("Charly");

        //start both not in games so good
        CHECK_NOTHROW(Game game(p1, p2););

        //one or more in game throw exception
        CHECK_THROWS_AS(Game game1(p3, p2), const std::invalid_argument&);
        CHECK_THROWS_AS(Game game2(p1, p3), const std::invalid_argument&);
        CHECK_THROWS_AS(Game game3(p1, p2), const std::invalid_argument&);

    }
    SUBCASE("Testing one player with two games after first game ended -> NOT trow exception") {
        Player p4("Alice");
        Player p5("Bob");
        Game game(p4, p5);
        game.playAll();
        CHECK_NOTHROW(Game game1(p4, p5););
    }
}

TEST_CASE("play after end") {
    SUBCASE("Testing play turn() after play all() -> trow exception") {
        Player p4("Alice");
        Player p5("Bob");
        Game game(p4, p5);
        game.playAll();
        CHECK_THROWS(game.playTurn());
    }
    SUBCASE("Testing play all() after play all() -> trow exception") {
        Player p4("Alice");
        Player p5("Bob");
        Game game(p4, p5);
        game.playAll();
        CHECK_THROWS(game.playAll());
    }
    SUBCASE("Testing play turn() 26 times -> trow exception") {
        Player p1("Alice");
        Player p2("Bob");
        Game game(p1, p2);
        for (int i = 0; i < 26; ++i) {
            //if game done with draws so wont throw exception
            try {
                game.playTurn();
            } catch (...) { break; }
        }
        //the 27 time surely throw exception
        CHECK_THROWS(game.playTurn());
    }
}

TEST_CASE("print log at start") {
    SUBCASE("last turn log -> trow exception") {
        Player p4("Alice");
        Player p5("Bob");
        Game game(p4, p5);

        CHECK_THROWS(game.printLastTurn());
    }
    SUBCASE("all log -> trow exception ") {
        Player p4("Alice");
        Player p5("Bob");
        Game game(p4, p5);

        CHECK_THROWS(game.printLog());
    }
}
TEST_CASE("print log NOT at start") {
    SUBCASE("last turn log -> NOT trow exception") {
        Player p4("Alice");
        Player p5("Bob");
        Game game(p4, p5);
        game.playTurn();
        CHECK_NOTHROW(game.printLastTurn());
    }
    SUBCASE("all log -> trow exception ") {
        Player p4("Alice");
        Player p5("Bob");
        Game game(p4, p5);
        game.playAll();
        CHECK_NOTHROW(game.printLog());
    }
}

TEST_CASE("print winner not on end game") {
    SUBCASE("Testing on start -> trow exception") {
        Player p4("Alice");
        Player p5("Bob");
        Game game(p4, p5);

        CHECK_THROWS(game.printWiner());
    }
    SUBCASE("Testing on middle -> trow exception ") {
        Player p4("Alice");
        Player p5("Bob");
        Game game(p4, p5);

        game.playTurn();
        //only if game dosent ended
        if (p4.stacksize() != 0 && p5.stacksize() != 0)
            CHECK_THROWS(game.printWiner());
    }

}
TEST_CASE("print winner on end game") {
    SUBCASE("Testing one end -> not trow exception") {
        Player p4("Alice");
        Player p5("Bob");
        Game game(p4, p5);

        game.playAll();
        CHECK_NOTHROW(game.printWiner());
    }
}


//assume printStats() is about player and not about game so wont trow even with no game or middle of game
TEST_CASE("print stats") {
    SUBCASE("Testing fresh player -> not trow exception") {
        Player p4("Alice");
        Player p5("Bob");
        Game game(p4, p5);

        CHECK_NOTHROW(game.printStats());
    }
    SUBCASE("Testing after turn player -> not trow exception") {
        Player p4("Alice");
        Player p5("Bob");
        Game game(p4, p5);

        game.playTurn();
        CHECK_NOTHROW(game.printStats());
    }
    SUBCASE("Testing after game player -> not trow exception") {
        Player p4("Alice");
        Player p5("Bob");
        Game game(p4, p5);

        game.playAll();
        CHECK_NOTHROW(game.printStats());
    }
}
