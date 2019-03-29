#pragma once

#include "move.hpp"

#include <array>
#include <map>
#include <set>

#include "tl/expected.hpp"

#include <boost/optional.hpp>

namespace Aronda
{

static const std::size_t c_number_of_players = 2;

static const std::size_t c_number_of_squares = 25;

enum class InvalidMove
{
    TooManyStones,
    SquareLocked,
    SquareUnreachable
};

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
    using ExpectedBoard = tl::expected<Board, InvalidMove>;

    /**
     * @brief construct an empty board
     */
    Board();

    SquareState squareState(const Square square) const;

    ExpectedBoard placeStone(const Move move) const;

    static std::size_t maxNumberOfStonesOnASquare(const Square square_index);

private:
    std::array<SquareState, c_number_of_squares> m_square_states;

    bool isSquareReachable(const Move move) const;

    static bool isSquareOnTheOutsideRing(const Square square);

    static std::set<Square> findNeighbours(const Square square);
};

} // namespace Aronda
