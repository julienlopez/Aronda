#include "board.hpp"

#include <gsl/gsl_util>

#include <boost/units/quantity.hpp>
#include <boost/units/systems/si/plane_angle.hpp>

#include <QPainter>

namespace Aronda
{

namespace
{
	using Angle_t = boost::units::quantity<boost::units::si::plane_angle>;
	const auto PI = 3.14159265359 * boost::units::si::radians;

    QPointF toPoint(const double r, const Angle_t angle)
    {
        return {r * std::cos(angle.value()), r * std::sin(angle.value())};
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
    drawCircles(p, outter_radius);
    drawLines(p, outter_radius);
	drawMaxmimumsInSquares(p, outter_radius);
}

void Board::drawCircles(QPainter& p, const int outter_radius) const
{
	p.drawEllipse({ 0,0 }, outter_radius, outter_radius);
    p.drawEllipse({ 0,0 }, 3 * outter_radius / 4, 3 * outter_radius / 4);
    p.drawEllipse({ 0,0 }, outter_radius / 2, outter_radius / 2);
    p.drawEllipse({ 0,0 }, outter_radius / 4, outter_radius / 4);
}

void Board::drawLines(QPainter& p, const int outter_radius) const
{
    for(int i = 0; i < 8; i++) // second circle for the center
    {
        const auto angle = i / 4. * PI;
        p.drawLine(QLineF(toPoint(outter_radius / 4, angle), toPoint(outter_radius / 2, angle)));
    }
    for(int i = 0; i < 8; i++) // third circle for the center
    {
		const auto angle = (i + 0.5) * PI / 4.;
        p.drawLine(QLineF(toPoint(outter_radius / 2, angle), toPoint(3 * outter_radius / 4, angle)));
    }
    for(int i = 0; i < 4; i++) // fourth circle for the center
    {
		auto angle = (4 * i + 0.5) * PI / 8.;
        p.drawLine(QLineF(toPoint(3 * outter_radius / 4, angle), toPoint(outter_radius, angle)));
        angle = (4 * i - 0.5) * PI / 8.;
        p.drawLine(QLineF(toPoint(3 * outter_radius / 4, angle), toPoint(outter_radius, angle)));
    }
}

void Board::drawMaxmimumsInSquares(QPainter& p, const int outter_radius) const
{
	const double dot_size = 4;
	p.save();
	p.setBrush(Qt::black);
	// inner circle
	const auto dist = outter_radius / 16;
	p.drawEllipse(QPointF(dist, dist), dot_size, dot_size);
	p.drawEllipse(QPointF(dist, -dist), dot_size, dot_size);
	p.drawEllipse(QPointF(-dist, dist), dot_size, dot_size);
	p.drawEllipse(QPointF(-dist, -dist), dot_size, dot_size);
	for (int i = 0; i < 4; i++) // third row
	{
		const auto angle = 4 * i / 8. * PI;
		const auto min_dist = outter_radius / 2;
		const auto max_dist = 3 * outter_radius / 4;
		p.drawEllipse(toPoint((max_dist - min_dist) / 3. + min_dist, angle), dot_size, dot_size);
		p.drawEllipse(toPoint(2 * (max_dist - min_dist) / 3. + min_dist, angle), dot_size, dot_size);
		p.drawEllipse(toPoint((max_dist - min_dist) / 2. + min_dist, angle + PI / 5. / 8.), dot_size, dot_size);
		p.drawEllipse(toPoint((max_dist - min_dist) / 2. + min_dist, angle - PI / 5. / 8.), dot_size, dot_size);
	}
	for (int i = 0; i < 4; i++) // fourth row
	{
		const auto angle = 4 * i / 8. * PI;
		const auto min_dist = 3 * outter_radius / 4;
		const auto max_dist = outter_radius;
		p.drawEllipse(toPoint((max_dist - min_dist) / 3. + min_dist, angle), dot_size, dot_size);
		p.drawEllipse(toPoint(2 * (max_dist - min_dist) / 3. + min_dist, angle), dot_size, dot_size);
	}
	p.restore();
}

}
