#pragma once

#include "gamesquare.hpp"

#include "move.hpp"
#include "square.hpp"

#include <boost/optional.hpp>

#include <QWidget>

namespace Aronda
{

class Game;

class BoardWidget : public QWidget
{
public:
    struct PolarPoint
    {
        double radius;
        Angle_t angle;
    };

    explicit BoardWidget(Game& game, QWidget* parent = nullptr);

    virtual ~BoardWidget() = default;

protected:
    virtual void resizeEvent(QResizeEvent* evt) override;

    virtual void paintEvent(QPaintEvent* evt) override;

    virtual void mouseMoveEvent(QMouseEvent* evt) override;

private:
    Game& m_game;
    GameSquareContainer_t m_squares;
    boost::optional<Square> m_current_square;

    void drawCircles(QPainter& p) const;

    void drawLines(QPainter& p) const;

    void drawMaxmimumsInSquares(QPainter& p) const;

    void drawCurrentSquare(QPainter& p) const;

    boost::optional<Square> findSquare(const PolarPoint& p) const;

    bool isSquarePlayable(const Square square) const;

    Move buildMoveForSquare(const Square square) const;
};
} // Aronda
