#pragma once

#include "forbiddenmove.hpp"
#include "player.hpp"
#include "square.hpp"

#include <array>
#include <map>
#include <set>

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

using AdjacencyList_t = std::map<Square, std::set<Square>>;

bool operator==(const SquareState& ss1, const SquareState& ss2);

class Board
{
public:
    Board();

    SquareState squareState(const Square square_index) const;

    void placeStone(Square square_index, Player player_index, const std::size_t number_of_stones);

    static std::size_t maxNumberOfStonesOnASquare(const Square square_index);

private:
    std::array<SquareState, c_number_of_squares> m_square_states;
};
}
