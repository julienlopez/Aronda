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
	virtual void resizeEvent(QResizeEvent* evt) override;

    virtual void paintEvent(QPaintEvent* evt) override;

private:
	GameSquareContainer_t m_squares;

    void drawCircles(QPainter& p) const;

    void drawLines(QPainter& p) const;

    void drawMaxmimumsInSquares(QPainter& p) const;
};
}
