#include "board.hpp"

#include "game.hpp"

#include <gsl/gsl_util>

#include <QPainter>

#include <iostream>

namespace Aronda
{

namespace
{

	struct PolarPoint
	{
		double radius;
		Angle_t angle;
	};

    QPointF toPoint(const PolarPoint& p)
    {
        return {p.radius * std::cos(p.angle.value()), p.radius * std::sin(p.angle.value())};
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
	p.translate(width() / 2, height() / 2);
	const auto squares = buildSquares(outter_radius);
    drawCircles(p, outter_radius);
    drawLines(p, squares);
	drawMaxmimumsInSquares(p, squares);
}

void Board::drawCircles(QPainter& p, const int outter_radius) const
{
	p.drawEllipse({ 0,0 }, outter_radius, outter_radius);
    p.drawEllipse({ 0,0 }, 3 * outter_radius / 4, 3 * outter_radius / 4);
    p.drawEllipse({ 0,0 }, outter_radius / 2, outter_radius / 2);
    p.drawEllipse({ 0,0 }, outter_radius / 4, outter_radius / 4);
}

void Board::drawLines(QPainter& p, const GameSquareContainer_t& squares) const
{
	auto it = begin(squares);
	std::advance(it, 1);
	for (; it != end(squares); ++it)
	{
		p.drawLine(QLineF(toPoint({ it->inner_radius, it->min_angle }), toPoint({ it->outter_radius, it->min_angle })));
		p.drawLine(QLineF(toPoint({ it->inner_radius, it->max_angle }), toPoint({ it->outter_radius, it->max_angle })));
	}
}

void Board::drawMaxmimumsInSquares(QPainter& p, const GameSquareContainer_t& squares) const
{
	const double dot_size = 4;
	p.save();
	p.setBrush(Qt::black);
	// inner circle
	const auto dist = squares.back().outter_radius / 16;
	p.drawEllipse(QPointF(dist, dist), dot_size, dot_size);
	p.drawEllipse(QPointF(dist, -dist), dot_size, dot_size);
	p.drawEllipse(QPointF(-dist, dist), dot_size, dot_size);
	p.drawEllipse(QPointF(-dist, -dist), dot_size, dot_size);

	for (const auto square_id : { 9, 11, 13, 15 }) // third row
	{
		const auto& square = squares[square_id];
		const auto angle = (square.max_angle + square.min_angle) / 2.;
		const auto min_dist = square.inner_radius;
		const auto max_dist = square.outter_radius;
		p.drawEllipse(toPoint({ (max_dist - min_dist) / 3. + min_dist, angle }), dot_size, dot_size);
		p.drawEllipse(toPoint({ 2 * (max_dist - min_dist) / 3. + min_dist, angle }), dot_size, dot_size);
		p.drawEllipse(toPoint({ (max_dist - min_dist) / 2. + min_dist, angle + PI / 5. / 8. }), dot_size, dot_size);
		p.drawEllipse(toPoint({ (max_dist - min_dist) / 2. + min_dist, angle - PI / 5. / 8. }), dot_size, dot_size);
	}
	for (const auto square_id : { 17, 19, 21, 23 }) // fourth row
	{
		const auto& square = squares[square_id];
		const auto angle = (square.max_angle + square.min_angle) / 2.;
		const auto min_dist = square.inner_radius;
		const auto max_dist = square.outter_radius;
		p.drawEllipse(toPoint({ (max_dist - min_dist) / 3. + min_dist, angle }), dot_size, dot_size);
		p.drawEllipse(toPoint({ 2 * (max_dist - min_dist) / 3. + min_dist, angle }), dot_size, dot_size);
	}
	p.restore();
}

}
