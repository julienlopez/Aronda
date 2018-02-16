#include "catch.hpp"

#include "game.hpp"

using Aronda::Game;

TEST_CASE("Testing basic game properties", "[game]")
{
    SECTION("Clean Game Properties")
    {
        Game g;
        CHECK(g.numberOfPlayers() == 2);
        CHECK(g.numberOfSquares() == 25);
    }
}
