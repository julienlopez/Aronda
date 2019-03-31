#include "board.hpp"

namespace Aronda
{

namespace
{
    Square operator"" _s(unsigned long long int i)
    {
        return Square(i);
    }

    AdjacencyList_t buildAdjacencyList()
    {
        return {{0_s, {1_s, 2_s, 3_s, 4_s, 5_s, 6_s, 7_s}}, {1_s, {0_s, 2_s, 8_s, 9_s, 10_s}},
                {2_s, {0_s, 1_s, 3_s, 10_s, 11_s}},         {3_s, {0_s, 2_s, 4_s, 11_s, 12_s}},
                {4_s, {0_s, 3_s, 5_s, 12_s, 13_s}},         {5_s, {0_s, 4_s, 6_s, 13_s, 14_s}},
                {6_s, {0_s, 5_s, 7_s, 14_s, 15_s}},         {7_s, {0_s, 6_s, 8_s, 15_s, 16_s}},
                {8_s, {0_s, 1_s, 7_s, 9_s, 16_s}},          {9_s, {1_s, 8_s, 10_s, 16_s, 17_s, 18_s, 24_s}},
                {10_s, {1_s, 2_s, 9_s, 11_s, 18_s}},        {11_s, {2_s, 3_s, 10_s, 12_s, 18_s, 19_s, 20_s}},
                {12_s, {3_s, 4_s, 11_s, 13_s, 20_s}},       {13_s, {4_s, 5_s, 12_s, 14_s, 20_s, 21_s, 22_s}},
                {14_s, {5_s, 6_s, 13_s, 15_s, 22_s}},       {15_s, {6_s, 7_s, 14_s, 16_s, 22_s, 23_s, 24_s}},
                {16_s, {7_s, 8_s, 9_s, 15_s, 24_s}},        {17_s, {9_s, 18_s, 24_s}},
                {18_s, {9_s, 10_s, 11_s, 17_s, 19_s}},      {19_s, {11_s, 18_s, 20_s}},
                {20_s, {11_s, 12_s, 13_s, 19_s, 21_s}},     {21_s, {13_s, 20_s, 22_s}},
                {22_s, {13_s, 14_s, 15_s, 21_s, 23_s}},     {23_s, {15_s, 22_s, 24_s}},
                {24_s, {9_s, 15_s, 16_s, 17_s, 23_s}}};
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
    using std::placeholders::_1;
    return std::find_if(begin(neighbouring_squares), end(neighbouring_squares),
                        std::bind(std::mem_fn(&Board::hasPlayerPlayerOnSquare), this, move.player_index, _1))
           != end(neighbouring_squares);
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

bool Board::hasPlayerPlayerOnSquare(const Player player, const Square square) const
{
    const auto& square_state = m_square_states[square];
    return square_state.placed_stones[player] > 0;
}
}
