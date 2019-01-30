#include "game.hpp"

namespace Aronda
{
Game::Game()
    : m_history(1)
{
}

const Board& Game::currentState() const
{
    return m_history.back();
}

tl::expected<void, InvalidMove> Game::placeStone(const Move move)
{
    return m_history.back().placeStone(move).map([this](Board b) { m_history.push_back(std::move(b)); });
}

Player Game::currentPlayer() const
{
    if(m_history.size() == 1) return Player{0};
    return ((m_history.size() - 2) % 4) < 2 ? Player{1} : Player{0};
}

std::size_t Game::stonesLeftToPlay() const
{
    return m_history.size() % 2 == 0 ? 2 : 1;
}

} // namespace Aronda
