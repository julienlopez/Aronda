#include "mainwindow.hpp"

#include "boardwidget.hpp"

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

    m_board_widget = new Aronda::BoardWidget;
    vl->addWidget(m_board_widget);

    w->setLayout(vl);
    setCentralWidget(w);
}

MainWindow::~MainWindow() = default;

} // namespace Aronda
