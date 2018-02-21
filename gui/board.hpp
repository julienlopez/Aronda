#pragma once

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
    void drawCircles(QPainter& p, const QPoint& center, const int outter_radius) const;

    void drawLines(QPainter& p, const QPoint& center, const int outter_radius) const;

	void drawMaxmimumsInSquares(QPainter& p, const QPoint& center, const int outter_radius) const;
};

}
