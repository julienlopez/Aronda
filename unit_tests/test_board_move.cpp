#include <catch.hpp>

#include "board.hpp"

#include <numeric_range.hpp>

#include <boost/optional/optional_io.hpp>

using Aronda::Board;

TEST_CASE("Testing placing a stone on en empty board", "[board]")
{
    Board g;

    SECTION("Playing 1 stone on an empty 3 capacity square")
    {
        Aronda::Square s{18};
        CHECK(g.squareState(s) == Aronda::SquareState{{0, 0}, {}});

        const auto res = g.placeStone({s, Aronda::black, 1});
        REQUIRE(res.has_value());
        CHECK(res->squareState(s) == Aronda::SquareState{{1, 0}, {}});
    }

    SECTION("Playing 2 stone on an empty 3 capacity square")
    {
        Aronda::Square s{18};
        CHECK(g.squareState(s) == Aronda::SquareState{{0, 0}, {}});

        const auto res = g.placeStone({s, Aronda::black, 2});
        REQUIRE(res.has_value());
        CHECK(res->squareState(s) == Aronda::SquareState{{2, 0}, {}});
    }

    SECTION("Playing a third stone on an empty 3 capacity square locks it")
    {
        Aronda::Square s{18};
        CHECK(g.squareState(s) == Aronda::SquareState{{0, 0}, {}});

        const auto res1 = g.placeStone({s, Aronda::black, 2});
        REQUIRE(res1.has_value());
        CHECK(res1->squareState(s) == Aronda::SquareState{{2, 0}, {}});

        const auto res2 = res1->placeStone({s, Aronda::black, 1});
        REQUIRE(res2.has_value());
        CHECK(res2->squareState(s) == Aronda::SquareState{{3, 0}, {Aronda::black}});
    }

    SECTION("Trying to place a fourth stone on an 3 capacity square is forbidden")
    {
        Aronda::Square s{18};
        CHECK(g.squareState(s) == Aronda::SquareState{{0, 0}, {}});

        const auto res1 = g.placeStone({s, Aronda::black, 2});
        REQUIRE(res1.has_value());
        CHECK(res1->squareState(s) == Aronda::SquareState{{2, 0}, {}});

        const auto res2 = res1->placeStone({s, Aronda::black, 2});
        REQUIRE(!res2.has_value());
        CHECK(res2.error() == Aronda::InvalidMove::TooManyStones);
    }

    SECTION("Playing 1 stone on an empty 2 capacity square")
    {
        Aronda::Square s{19};
        CHECK(g.squareState(s) == Aronda::SquareState{{0, 0}, {}});

        const auto res = g.placeStone({s, Aronda::black, 1});
        REQUIRE(res.has_value());
        CHECK(res->squareState(s) == Aronda::SquareState{{1, 0}, {}});
    }

    SECTION("Playing 2 stone on an empty 2 capacity square locks it")
    {
        Aronda::Square s{19};
        CHECK(g.squareState(s) == Aronda::SquareState{{0, 0}, {}});

        const auto res = g.placeStone({s, Aronda::black, 2});
        REQUIRE(res.has_value());
        CHECK(res->squareState(s) == Aronda::SquareState{{2, 0}, {Aronda::black}});
    }

    SECTION("Trying to place a third stone on a 2 capacity square is forbidden")
    {
        Aronda::Square s{19};
        CHECK(g.squareState(s) == Aronda::SquareState{{0, 0}, {}});

        const auto res1 = g.placeStone({s, Aronda::black, 2});
        REQUIRE(res1.has_value());
        CHECK(res1->squareState(s) == Aronda::SquareState{{2, 0}, {Aronda::black}});

        const auto res2 = res1->placeStone({s, Aronda::black, 1});
        REQUIRE(!res2.has_value());
        CHECK(res2.error() == Aronda::InvalidMove::SquareLocked);
    }

    SECTION("Trying to place four stones on a 2 capacity square is forbidden")
    {
        Aronda::Square s{19};
        CHECK(g.squareState(s) == Aronda::SquareState{{0, 0}, {}});

        const auto res1 = g.placeStone({s, Aronda::black, 2});
        REQUIRE(res1.has_value());
        CHECK(res1->squareState(s) == Aronda::SquareState{{2, 0}, {Aronda::black}});

        const auto res2 = res1->placeStone({s, Aronda::black, 2});
        REQUIRE(!res2.has_value());
        CHECK(res2.error() == Aronda::InvalidMove::SquareLocked);
    }

    SECTION("Trying to place a stone on the fourth ring on an empty board should be possible")
    {
        for(const auto square : range<std::size_t>(17, 25))
        {
            std::wcout << square << std::endl;
            const auto res = g.placeStone({Aronda::Square{square}, Aronda::black, 1});
            REQUIRE(res.has_value());
        }
    }

    SECTION("Trying to place a stone on the second ring on an empty board should fail")
    {
        for(const auto square : range<std::size_t>(9, 17))
        {
            std::wcout << square << std::endl;
            const auto res = g.placeStone({Aronda::Square{square}, Aronda::black, 1});
            REQUIRE(!res.has_value());
            CHECK(res.error() == Aronda::InvalidMove::SquareUnreachable);
        }
    }

    SECTION("Trying to place a stone on the third ring on an empty board should fail")
    {
        for(const auto square : range<std::size_t>(1, 9))
        {
            std::wcout << square << std::endl;
            const auto res = g.placeStone({Aronda::Square{square}, Aronda::black, 1});
            REQUIRE(!res.has_value());
            CHECK(res.error() == Aronda::InvalidMove::SquareUnreachable);
        }
    }

    SECTION("Trying to place a stone on the central square on an empty board should fail")
    {
        const auto res = g.placeStone({Aronda::Square{0}, Aronda::black, 1});
        REQUIRE(!res.has_value());
        CHECK(res.error() == Aronda::InvalidMove::SquareUnreachable);
    }
}
