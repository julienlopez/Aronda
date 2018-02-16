#pragma once

#include "player.hpp"
#include "square.hpp"

#include <array>

#include <boost/optional.hpp>

namespace Aronda
{

static const std::size_t c_number_of_players = 2;

static const std::size_t c_number_of_squares = 25;

struct SquareState
{
    std::array<std::size_t, c_number_of_players> placed_stones;
    boost::optional<Player> player_locked;
};

class Game
{
public:
    Game() = default;

    SquareState squareState(const Square square_index) const;

    static std::size_t maxNumberOfStonesOnASquare(const Square square_index);
};
}
