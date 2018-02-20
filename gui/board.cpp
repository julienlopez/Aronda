#include "board.hpp"

#include <QPainter>

namespace Aronda
{

namespace
{
    const double PI = 3.14159265359;

    QPointF toPoint(double r, double angle)
    {
        return {r * std::cos(angle), r * std::sin(angle)};
    }
}

Board::Board(QWidget* parent)
    : QWidget(parent)
{
    setMinimumSize(600, 600);
}

void Board::paintEvent(QPaintEvent* evt)
{
    QPainter p(this);
    const auto size = (int)(std::min(width(), height()) * 0.95);
    const auto outter_radius = size / 2;
    const QPoint center(width() / 2, height() / 2);
    drawCircles(p, center, outter_radius);
    drawLines(p, center, outter_radius);
}

void Board::drawCircles(QPainter& p, const QPoint& center, const int outter_radius) const
{
    p.drawEllipse(center, outter_radius, outter_radius);
    p.drawEllipse(center, 3 * outter_radius / 4, 3 * outter_radius / 4);
    p.drawEllipse(center, outter_radius / 2, outter_radius / 2);
    p.drawEllipse(center, outter_radius / 4, outter_radius / 4);
}

void Board::drawLines(QPainter& p, const QPoint& center, const int outter_radius) const
{
    for(int i = 0; i < 8; i++) // second circle for the center
    {
        double angle = i * PI / 4;
        p.drawLine(QLineF(center + toPoint(outter_radius / 4, angle), center + toPoint(outter_radius / 2, angle)));
    }
    for(int i = 0; i < 8; i++) // third circle for the center
    {
        double angle = (i + 0.5) * PI / 4;
        p.drawLine(QLineF(center + toPoint(outter_radius / 2, angle), center + toPoint(3 * outter_radius / 4, angle)));
    }
    for(int i = 0; i < 4; i++) // fourth circle for the center
    {
        double angle = (4 * i + 0.5) * PI / 8;
        p.drawLine(QLineF(center + toPoint(3 * outter_radius / 4, angle), center + toPoint(outter_radius, angle)));
        angle = (4 * i - 0.5) * PI / 8;
        p.drawLine(QLineF(center + toPoint(3 * outter_radius / 4, angle), center + toPoint(outter_radius, angle)));
    }
}
}
