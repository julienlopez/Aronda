#pragma once

#include "gamesquare.hpp"

#include <QWidget>

namespace Aronda
{

class Board : public QWidget
{
public:
    Board(QWidget* parent = nullptr);

    virtual ~Board() = default;

protected:
    virtual void paintEvent(QPaintEvent* evt) override;

private:
    void drawCircles(QPainter& p, const int outter_radius) const;

    void drawLines(QPainter& p, const GameSquareContainer_t& squares) const;

    void drawMaxmimumsInSquares(QPainter& p, const GameSquareContainer_t& squares) const;
};
}
