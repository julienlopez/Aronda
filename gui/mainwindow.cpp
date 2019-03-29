#include "mainwindow.hpp"

#include "boardwidget.hpp"
#include "playersstatewidget.hpp"

#include "game.hpp"

#include <QVBoxLayout>

namespace Aronda
{

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , m_game(std::make_unique<Game>())
{
    auto* w = new QWidget;
    auto* vl = new QVBoxLayout;

    m_players_state_widget = new PlayersStateWidget(*m_game);
    m_players_state_widget->setMinimumHeight(100);
    vl->addWidget(m_players_state_widget);

    m_board_widget = new Aronda::BoardWidget(*m_game);
    vl->addWidget(m_board_widget);

    w->setLayout(vl);
    setCentralWidget(w);

    m_players_state_widget->updateCurrentPlayer();
}

MainWindow::~MainWindow() = default;

} // namespace Aronda
