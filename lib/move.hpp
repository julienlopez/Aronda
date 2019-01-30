#pragma once

#include "player.hpp"
#include "square.hpp"

namespace Aronda
{

struct Move
{
    Square square_index;
    Player player_index;
    const std::size_t number_of_stones;
};
}
