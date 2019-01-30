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
    auto res = m_history.back().placeStone(move);
    if(res)
    {
        m_history.push_back(std::move(*res));
        return {};
    }
    else
        return tl::make_unexpected(res.error());
}

} // namespace Aronda
