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

        const auto res = g.placeStone(s, Aronda::Player(0), 1);
        REQUIRE(res.has_value());
        CHECK(res->squareState(s) == Aronda::SquareState{{1, 0}, {}});
    }

    SECTION("Playing 2 stone on an empty 3 capacity square")
    {
        Aronda::Square s{18};
        CHECK(g.squareState(s) == Aronda::SquareState{{0, 0}, {}});

        const auto res = g.placeStone(s, Aronda::Player(0), 2);
        REQUIRE(res.has_value());
        CHECK(res->squareState(s) == Aronda::SquareState{{2, 0}, {}});
    }

    SECTION("Playing a third stone on an empty 3 capacity square locks it")
    {
        Aronda::Square s{18};
        CHECK(g.squareState(s) == Aronda::SquareState{{0, 0}, {}});

        const auto res1 = g.placeStone(s, Aronda::Player(0), 2);
        REQUIRE(res1.has_value());
        CHECK(res1->squareState(s) == Aronda::SquareState{{2, 0}, {}});

        const auto res2 = res1->placeStone(s, Aronda::Player(0), 1);
        REQUIRE(res2.has_value());
        CHECK(res2->squareState(s) == Aronda::SquareState{{3, 0}, {Aronda::Player(0)}});
    }

    SECTION("Trying to place a fourth stone on an 3 capacity square is forbidden")
    {
        Aronda::Square s{18};
        CHECK(g.squareState(s) == Aronda::SquareState{{0, 0}, {}});

        const auto res1 = g.placeStone(s, Aronda::Player(0), 2);
        REQUIRE(res1.has_value());
        CHECK(res1->squareState(s) == Aronda::SquareState{{2, 0}, {}});

        const auto res2 = res1->placeStone(s, Aronda::Player(0), 2);
        REQUIRE(!res2.has_value());
        CHECK(res2.error() == Aronda::InvalidMove::TooManyStones);
    }

    SECTION("Playing 1 stone on an empty 2 capacity square")
    {
        Aronda::Square s{19};
        CHECK(g.squareState(s) == Aronda::SquareState{{0, 0}, {}});

        const auto res = g.placeStone(s, Aronda::Player(0), 1);
        REQUIRE(res.has_value());
        CHECK(res->squareState(s) == Aronda::SquareState{{1, 0}, {}});
    }

    SECTION("Playing 2 stone on an empty 2 capacity square locks it")
    {
        Aronda::Square s{19};
        CHECK(g.squareState(s) == Aronda::SquareState{{0, 0}, {}});

        const auto res = g.placeStone(s, Aronda::Player(0), 2);
        REQUIRE(res.has_value());
        CHECK(res->squareState(s) == Aronda::SquareState{{2, 0}, {Aronda::Player(0)}});
    }

    SECTION("Trying to place a third stone on a 2 capacity square is forbidden")
    {
        Aronda::Square s{19};
        CHECK(g.squareState(s) == Aronda::SquareState{{0, 0}, {}});

        const auto res1 = g.placeStone(s, Aronda::Player(0), 2);
        REQUIRE(res1.has_value());
        CHECK(res1->squareState(s) == Aronda::SquareState{{2, 0}, {Aronda::Player(0)}});

        const auto res2 = res1->placeStone(s, Aronda::Player(0), 1);
        REQUIRE(!res2.has_value());
        CHECK(res2.error() == Aronda::InvalidMove::SquareLocked);
    }

    SECTION("Trying to place four stones on a 2 capacity square is forbidden")
    {
        Aronda::Square s{19};
        CHECK(g.squareState(s) == Aronda::SquareState{{0, 0}, {}});

        const auto res1 = g.placeStone(s, Aronda::Player(0), 2);
        REQUIRE(res1.has_value());
        CHECK(res1->squareState(s) == Aronda::SquareState{{2, 0}, {Aronda::Player(0)}});

        const auto res2 = res1->placeStone(s, Aronda::Player(0), 2);
        REQUIRE(!res2.has_value());
        CHECK(res2.error() == Aronda::InvalidMove::SquareLocked);
    }
}
