#pragma once

#include "player.hpp"
#include "square.hpp"

#include <utility>

namespace Aronda
{

class Game
{
public:
    Game() = default;

    static std::size_t numberOfPlayers();

    static std::size_t numberOfSquares();
};

}
