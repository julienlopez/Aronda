#include "board.hpp"

namespace Aronda
{

namespace
{
    AdjacencyList_t buildAdjacencyList()
    {
        using Aronda::Square;
        return {
			{Square(0), {}},  
			{Square(1), {}},  
			{Square(2), {}},  
			{Square(3), {}},  
			{Square(4), {}},  
			{Square(5), {}},  
			{Square(6), {}},  
			{Square(7), {}},  
			{Square(8), {}},
            {Square(9), {}}, 
			{Square(10), {}}, 
			{Square(11), {}}, 
			{Square(12), {}}, 
			{Square(13), {}}, 
			{Square(14), {}},
			{Square(15), {}},
			{Square(16), {}}, 
			{Square(17), {}},
            {Square(18), {}}, 
			{Square(19), {}}, 
			{Square(20), {}}, 
			{Square(21), {}}, 
			{Square(22), {}}, 
			{Square(23), {}}, 
			{Square(24), {}}};
    }
}

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

auto Board::placeStone(const Move move) const -> ExpectedBoard
{
    if(m_square_states[move.square_index].player_locked) return tl::make_unexpected(InvalidMove::SquareLocked);
    if(m_square_states[move.square_index].placed_stones[move.player_index] + move.number_of_stones
       > maxNumberOfStonesOnASquare(move.square_index))
        return tl::make_unexpected(InvalidMove::TooManyStones);
    if(!isSquareReachable(move)) return tl::make_unexpected(InvalidMove::SquareUnreachable);
    Board res = *this;
    res.m_square_states[move.square_index].placed_stones[move.player_index] += move.number_of_stones;
    if(res.m_square_states[move.square_index].placed_stones[move.player_index]
       == maxNumberOfStonesOnASquare(move.square_index))
    {
        res.m_square_states[move.square_index].player_locked = move.player_index;
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

bool Board::isSquareReachable(const Move move) const
{
    if(isSquareOnTheOutsideRing(move.square_index)) return true;
    const auto neighbouring_squares = findNeighbours(move.square_index);
    return false;
}

bool Board::isSquareOnTheOutsideRing(const Square square)
{
    return square >= 17;
}

std::set<Square> Board::findNeighbours(const Square square)
{
    static const auto adjacencty_list = buildAdjacencyList();
    return adjacencty_list.at(square);
}
}
