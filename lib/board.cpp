#include "board.hpp"

namespace Aronda
{

bool operator==(const SquareState& ss1, const SquareState& ss2)
{
    return ss1.placed_stones == ss2.placed_stones && ss1.player_locked == ss2.player_locked;
}

Board::Board()
{
    std::fill(begin(m_square_states), end(m_square_states), SquareState{{0, 0}, {}});
}

SquareState Board::squareState(const Square square_index) const
{
    return m_square_states[square_index];
}

tl::expected<Board, InvalidMove> Board::placeStone(Square square_index, Player player_index,
                                                   const std::size_t number_of_stones) const
{
    if(m_square_states[square_index].placed_stones[player_index] + number_of_stones
       > maxNumberOfStonesOnASquare(square_index))
        return tl::make_unexpected(InvalidMove::TooManyStones);
    Board res;
    res.m_square_states[square_index].placed_stones[player_index] += number_of_stones;
    if(res.m_square_states[square_index].placed_stones[player_index] == maxNumberOfStonesOnASquare(square_index))
    {
        res.m_square_states[square_index].player_locked = player_index;
    }
    return res;
}

std::size_t Board::maxNumberOfStonesOnASquare(const Square square_index)
{
    switch(static_cast<std::size_t>(square_index))
    {
    case 0:
    case 9:
    case 11:
    case 13:
    case 15:
        return 4;
    case 17:
    case 19:
    case 21:
    case 23:
        return 2;
    default:
        return 3;
    }
}
}
