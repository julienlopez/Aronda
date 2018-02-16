#include <catch.hpp>

#include "game.hpp"

#include <numeric_range.hpp>

using Aronda::Game;

TEST_CASE("Testing basic game properties", "[game]")
{
    SECTION("Clean Game Properties")
    {
        Game g;
        CHECK(g.numberOfPlayers() == 2);
        CHECK(g.numberOfSquares() == 25);
    }

	SECTION("Max number of stones on a sqaure")
	{

	}
}
