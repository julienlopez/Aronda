#include "game.hpp"

namespace Aronda
{

SquareState Game::squareState(const Square square_index) const
{
    return {{0, 0}, boost::none};
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
