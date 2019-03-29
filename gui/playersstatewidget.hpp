#pragma once

#include "player.hpp"

#include <QWidget>

namespace Aronda
{

class Game;

namespace Impl
{
    class PlayerSquare;
}

class PlayersStateWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PlayersStateWidget(const Game& game, QWidget* parent = nullptr);

    virtual ~PlayersStateWidget() = default;

public slots:
    void updateCurrentPlayer();

private:
    const Game& m_game;
    std::map<Player, Impl::PlayerSquare*> m_squares;
};

} // namespace Aronda
