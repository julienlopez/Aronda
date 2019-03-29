#pragma once

#include <memory>

#include <QMainWindow>

namespace Aronda
{

class BoardWidget;
class Game;

class MainWindow : public QMainWindow
{
public:
    explicit MainWindow(QWidget* parent = nullptr);

    virtual ~MainWindow();

private:
    std::unique_ptr<Game> m_game;
    BoardWidget* m_board_widget;
};

} // namespace Aronda
