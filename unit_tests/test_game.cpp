#include <catch.hpp>

#include "game.hpp"

#include <numeric_range.hpp>

#include <boost/optional/optional_io.hpp>

using Aronda::Game;

TEST_CASE("Testing the game state placing a stone on en empty board", "[game]")
{
    Game g;

    SECTION("Playing 1 stone on an empty 3 capacity square")
    {
        Aronda::Square s{18};
        CHECK(g.currentState().squareState(s) == Aronda::SquareState{{0, 0}, {}});
        REQUIRE(g.placeStone({s, Aronda::black, 1}).has_value());
        CHECK(g.currentState().squareState(s) == Aronda::SquareState{{1, 0}, {}});
    }

    SECTION("Playing 2 stone on an empty 3 capacity square")
    {
        Aronda::Square s{18};
        CHECK(g.currentState().squareState(s) == Aronda::SquareState{{0, 0}, {}});
        CHECK_NOTHROW(g.placeStone({s, Aronda::black, 2}));
        CHECK(g.currentState().squareState(s) == Aronda::SquareState{{2, 0}, {}});
    }

    SECTION("Playing a third stone on an empty 3 capacity square locks it")
    {
        Aronda::Square s{18};
        CHECK(g.currentState().squareState(s) == Aronda::SquareState{{0, 0}, {}});
        REQUIRE(g.placeStone({s, Aronda::black, 2}).has_value());
        CHECK(g.currentState().squareState(s) == Aronda::SquareState{{2, 0}, {}});
        CHECK_NOTHROW(g.placeStone({s, Aronda::black, 1}));
        CHECK(g.currentState().squareState(s) == Aronda::SquareState{{3, 0}, {Aronda::black}});
    }

    SECTION("Trying to place a fourth stone on an 3 capacity square is forbidden")
    {
        Aronda::Square s{18};
        CHECK(g.currentState().squareState(s) == Aronda::SquareState{{0, 0}, {}});
        REQUIRE(g.placeStone({s, Aronda::black, 2}).has_value());
        CHECK(g.currentState().squareState(s) == Aronda::SquareState{{2, 0}, {}});
        const auto res = g.placeStone({s, Aronda::black, 2});
        REQUIRE(!res.has_value());
        CHECK(res.error() == Aronda::InvalidMove::TooManyStones);
        CHECK(g.currentState().squareState(s) == Aronda::SquareState{{2, 0}, {}});
    }

    SECTION("Playing 1 stone on an empty 2 capacity square")
    {
        Aronda::Square s{19};
        CHECK(g.currentState().squareState(s) == Aronda::SquareState{{0, 0}, {}});
        REQUIRE(g.placeStone({s, Aronda::black, 1}).has_value());
        CHECK(g.currentState().squareState(s) == Aronda::SquareState{{1, 0}, {}});
    }

    SECTION("Playing 2 stone on an empty 2 capacity square locks it")
    {
        Aronda::Square s{19};
        CHECK(g.currentState().squareState(s) == Aronda::SquareState{{0, 0}, {}});
        REQUIRE(g.placeStone({s, Aronda::black, 2}).has_value());
        CHECK(g.currentState().squareState(s) == Aronda::SquareState{{2, 0}, {Aronda::black}});
    }

    SECTION("Trying to place a stone on a locked square is forbidden")
    {
        Aronda::Square s{19};
        CHECK(g.currentState().squareState(s) == Aronda::SquareState{{0, 0}, {}});
        REQUIRE(g.placeStone({s, Aronda::black, 2}).has_value());
        CHECK(g.currentState().squareState(s) == Aronda::SquareState{{2, 0}, {Aronda::black}});
        const auto res = g.placeStone({s, Aronda::black, 1});
        REQUIRE(!res.has_value());
        CHECK(res.error() == Aronda::InvalidMove::SquareLocked);
        CHECK(g.currentState().squareState(s) == Aronda::SquareState{{2, 0}, {Aronda::black}});
    }
}

TEST_CASE("Testing the current player in the game state", "[game]")
{
    Game g;

    SECTION("Black to play only one stone when starting a game")
    {
        CHECK(g.currentPlayer() == Aronda::black);
        CHECK(g.stonesLeftToPlay() == 1);
    }

    SECTION("First couple of moves to check whose turn is it and how many moves he should play")
    {
        REQUIRE(g.placeStone({Aronda::Square{19}, Aronda::black, 1}).has_value());
        CHECK(g.currentPlayer() == Aronda::white);
        CHECK(g.stonesLeftToPlay() == 2);

        REQUIRE(g.placeStone({Aronda::Square{21}, Aronda::white, 1}).has_value());
        CHECK(g.currentPlayer() == Aronda::white);
        CHECK(g.stonesLeftToPlay() == 1);

        REQUIRE(g.placeStone({Aronda::Square{21}, Aronda::white, 1}).has_value());
        CHECK(g.currentPlayer() == Aronda::black);
        CHECK(g.stonesLeftToPlay() == 2);
    }
}
