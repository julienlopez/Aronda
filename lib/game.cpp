#include "game.hpp"

namespace Aronda
{


bool operator==(const SquareState& ss1, const SquareState& ss2)
{
	return ss1.placed_stones == ss2.placed_stones && ss1.player_locked == ss2.player_locked;
}

Game::Game()
{
	std::fill(begin(m_square_states), end(m_square_states), SquareState{ { 0, 0 },{} });
}

SquareState Game::squareState(const Square square_index) const
{
	return m_square_states[square_index];
}

void Game::placeStone(Square square_index, Player player_index, const std::size_t number_of_stones)
{
	m_square_states[square_index].placed_stones[player_index] += number_of_stones;
}

std::size_t Game::maxNumberOfStonesOnASquare(const Square square_index)
{
    switch(square_index)
    {
    case 1:
    case 10:
    case 12:
    case 14:
    case 16:
        return 4;
    case 18:
    case 20:
    case 22:
    case 24:
        return 2;
    default:
        return 3;
    }
}
}
