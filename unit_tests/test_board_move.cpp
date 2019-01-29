#include <catch.hpp>

#include "board.hpp"

#include <numeric_range.hpp>

#include <boost/optional/optional_io.hpp>

using Aronda::Board;

TEST_CASE("Testing placing a stone on en empty board", "[game]")
{
    Board g;

    SECTION("Playing 1 stone on an empty 3 capacity square")
    {
        Aronda::Square s{18};
        CHECK(g.squareState(s) == Aronda::SquareState{{0, 0}, {}});
        CHECK_NOTHROW(g.placeStone(s, Aronda::Player(0), 1));
        CHECK(g.squareState(s) == Aronda::SquareState{{1, 0}, {}});
    }

    SECTION("Playing 2 stone on an empty 3 capacity square")
    {
        Aronda::Square s{18};
        CHECK(g.squareState(s) == Aronda::SquareState{{0, 0}, {}});
        CHECK_NOTHROW(g.placeStone(s, Aronda::Player(0), 2));
        CHECK(g.squareState(s) == Aronda::SquareState{{2, 0}, {}});
    }

    SECTION("Playing a third stone on an empty 3 capacity square locks it")
    {
        Aronda::Square s{18};
        CHECK(g.squareState(s) == Aronda::SquareState{{0, 0}, {}});
        CHECK_NOTHROW(g.placeStone(s, Aronda::Player(0), 2));
        CHECK(g.squareState(s) == Aronda::SquareState{{2, 0}, {}});
        CHECK_NOTHROW(g.placeStone(s, Aronda::Player(0), 1));
        CHECK(g.squareState(s) == Aronda::SquareState{{3, 0}, {Aronda::Player(0)}});
    }

    SECTION("Trying to place a fourth stone on an 3 capacity square is forbidden")
    {
        Aronda::Square s{18};
        CHECK(g.squareState(s) == Aronda::SquareState{{0, 0}, {}});
        CHECK_NOTHROW(g.placeStone(s, Aronda::Player(0), 2));
        CHECK(g.squareState(s) == Aronda::SquareState{{2, 0}, {}});
        CHECK_THROWS_AS(g.placeStone(s, Aronda::Player(0), 2), Aronda::ForbiddenMove);
        CHECK(g.squareState(s) == Aronda::SquareState{{2, 0}, {}});
    }

    SECTION("Playing 1 stone on an empty 2 capacity square")
    {
        Aronda::Square s{19};
        CHECK(g.squareState(s) == Aronda::SquareState{{0, 0}, {}});
        CHECK_NOTHROW(g.placeStone(s, Aronda::Player(0), 1));
        CHECK(g.squareState(s) == Aronda::SquareState{{1, 0}, {}});
    }

    SECTION("Playing 2 stone on an empty 2 capacity square locks it")
    {
        Aronda::Square s{19};
        CHECK(g.squareState(s) == Aronda::SquareState{{0, 0}, {}});
        CHECK_NOTHROW(g.placeStone(s, Aronda::Player(0), 2));
        CHECK(g.squareState(s) == Aronda::SquareState{{2, 0}, {Aronda::Player(0)}});
    }

    SECTION("Trying to place a third stone on a 2 capacity square is forbidden")
    {
        Aronda::Square s{19};
        CHECK(g.squareState(s) == Aronda::SquareState{{0, 0}, {}});
        CHECK_NOTHROW(g.placeStone(s, Aronda::Player(0), 2));
        CHECK(g.squareState(s) == Aronda::SquareState{{2, 0}, {Aronda::Player(0)}});
        CHECK_THROWS_AS(g.placeStone(s, Aronda::Player(0), 1), Aronda::ForbiddenMove);
        CHECK(g.squareState(s) == Aronda::SquareState{{2, 0}, {Aronda::Player(0)}});
    }

    SECTION("Trying to place four stones on a 2 capacity square is forbidden")
    {
        Aronda::Square s{19};
        CHECK(g.squareState(s) == Aronda::SquareState{{0, 0}, {}});
        CHECK_NOTHROW(g.placeStone(s, Aronda::Player(0), 2));
        CHECK(g.squareState(s) == Aronda::SquareState{{2, 0}, {Aronda::Player(0)}});
        CHECK_THROWS_AS(g.placeStone(s, Aronda::Player(0), 2), Aronda::ForbiddenMove);
        CHECK(g.squareState(s) == Aronda::SquareState{{2, 0}, {Aronda::Player(0)}});
    }
}
