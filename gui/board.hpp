#pragma once

#include "gamesquare.hpp"

#include "square.hpp"

#include <boost/optional.hpp>

#include <QWidget>

namespace Aronda
{

class Board : public QWidget
{
public:
    Board(QWidget* parent = nullptr);

    virtual ~Board() = default;

protected:
    virtual void resizeEvent(QResizeEvent* evt) override;

    virtual void paintEvent(QPaintEvent* evt) override;

private:
    GameSquareContainer_t m_squares;
    boost::optional<Square> m_current_square;

    void drawCircles(QPainter& p) const;

    void drawLines(QPainter& p) const;

    void drawMaxmimumsInSquares(QPainter& p) const;

    void drawCurrentSquare(QPainter& p) const;
};
}
