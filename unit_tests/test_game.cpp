#include <catch.hpp>

#include "game.hpp"

#include <numeric_range.hpp>

#include <boost/optional/optional_io.hpp>

using Aronda::Game;

TEST_CASE("Testing basic game properties", "[game]")
{
    SECTION("Clean Game Properties")
    {
        Game g;
        for(const auto square_index : range(Aronda::c_number_of_squares))
        {
            const auto state = g.squareState(Aronda::Square(square_index));
            CHECK(state.placed_stones[0] == 0);
            CHECK(state.placed_stones[1] == 0);
            CHECK(state.player_locked == boost::none);
        }
    }

    SECTION("Max number of stones on a square")
    {
        for(const auto i : range(Aronda::c_number_of_squares))
        {
            const auto max_nb_stones = Game::maxNumberOfStonesOnASquare(Aronda::Square(i));
            if(i == 17 || i == 19 || i == 21 || i == 23)
                CHECK(max_nb_stones == 2);
            else if(i == 0 || i == 9 || i == 11 || i == 13 || i == 15)
                CHECK(max_nb_stones == 4);
            else
                CHECK(max_nb_stones == 3);
        }
    }
}
