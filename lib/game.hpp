#pragma once

#include "board.hpp"

namespace Aronda
{

class Game
{
public:
    Game();
    ~Game() = default;

    const Board& currentState() const;

    tl::expected<void, InvalidMove> placeStone(const Move move);

    Player currentPlayer() const;

    std::size_t stonesLeftToPlay() const;

private:
    std::vector<Board> m_history;
};

} // namespace Aronda
