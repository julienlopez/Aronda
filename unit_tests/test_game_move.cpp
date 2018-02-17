#include <catch.hpp>

#include "game.hpp"

#include <numeric_range.hpp>

#include <boost/optional/optional_io.hpp>

using Aronda::Game;

TEST_CASE("Testing placing a stone on en empty board", "[game]")
{
    Game g;

    SECTION("Playing one stone on an empty 3 capacity square")
    {
        Aronda::Square s{19};
        CHECK(g.squareState(s) == Aronda::SquareState{{0, 0}, {}});
        CHECK_NOTHROW(g.placeStone(s, Aronda::Player(0), 1));
        CHECK(g.squareState(s) == Aronda::SquareState{{1, 0}, {}});
    }
}
