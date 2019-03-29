#include <catch.hpp>

#include "board.hpp"

#include <numeric_range.hpp>

#include <boost/optional/optional_io.hpp>

using Aronda::Board;
using Aronda::InvalidMove;
using Aronda::Square;
using Aronda::SquareState;

template <class T> bool contains(const std::vector<T>& container, const T& value)
{
    return std::find(begin(container), end(container), value) != end(container);
}

TEST_CASE("Testing playable moves throughout the game", "[board]")
{

    SECTION("Only the outside squares are playable on an empty board")
    {
        Board g;
        const std::vector<std::size_t> playable_moves = {17, 18, 19, 20, 21, 22, 23, 24};
        for(const auto square : range<std::size_t>(0, Aronda::c_number_of_squares))
        {
            const auto res = g.placeStone({Square{square}, Aronda::black, 1});
            if(contains(playable_moves, square))
            {
                CHECK(res.has_value());
            }
            else
            {
                REQUIRE(!res.has_value());
                CHECK(res.error() == InvalidMove::SquareUnreachable);
            }
        }
    }

    SECTION("Only the outside squares are playable for white's first move")
    {
        Board g;
        const auto res = g.placeStone({Square{24}, Aronda::black, 1});
        REQUIRE(res.has_value());
        const std::vector<std::size_t> playable_moves = {17, 18, 19, 20, 21, 22, 23, 24};
        for(const auto square : range<std::size_t>(0, Aronda::c_number_of_squares))
        {
            const auto res = g.placeStone({Square{square}, Aronda::white, 1});
            if(contains(playable_moves, square))
            {
                CHECK(res.has_value());
            }
            else
            {
                REQUIRE(!res.has_value());
                CHECK(res.error() == InvalidMove::SquareUnreachable);
            }
        }
    }
}
