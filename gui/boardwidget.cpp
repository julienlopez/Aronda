#include "boardwidget.hpp"

#include "game.hpp"

#include <gsl/gsl_util>

#include <QMouseEvent>
#include <QPainter>

using boost::units::si::radians;

namespace Aronda
{

namespace
{

    auto transformAngle(const Angle_t& a)
    {
        return PI / 2. - a;
    };

    QPointF toPoint(const BoardWidget::PolarPoint& p)
    {
        const auto a = transformAngle(p.angle);
        return {p.radius * std::cos(a.value()), -p.radius * std::sin(a.value())};
    }

    double toDegrees(const Angle_t a)
    {
        return 360. * a / 2. / PI;
    }
}

BoardWidget::BoardWidget(Game& game, QWidget* parent)
    : QWidget(parent)
    , m_game(game)
{
    setMinimumSize(600, 600);
    setMouseTracking(true);
}

void BoardWidget::resizeEvent(QResizeEvent* evt)
{
    QWidget::resizeEvent(evt);
    const auto size = (int)(std::min(width(), height()) * 0.95);
    const auto outter_radius = size / 2;
    m_squares = buildSquares(outter_radius);
}

void BoardWidget::paintEvent(QPaintEvent* evt)
{
    QPainter p(this);
    p.translate(width() / 2, height() / 2);
    auto pen = p.pen();
    pen.setWidth(2);
    p.setPen(pen);
    p.setRenderHint(QPainter::HighQualityAntialiasing);
    drawCurrentSquare(p);
    drawCircles(p);
    drawLines(p);
    drawMaxmimumsInSquares(p);
    drawStones(p);
}

void BoardWidget::mouseMoveEvent(QMouseEvent* evt)
{
    m_current_square = mousePosToSquare(evt->pos());
    update();
}

void BoardWidget::mouseReleaseEvent(QMouseEvent* evt)
{
    if(!m_current_square) return;
    const auto res = m_game.placeStone({*m_current_square, m_game.currentPlayer(), 1});
    if(res)
    {
        update();
        emit movePlayed();
    }
}

void BoardWidget::drawCircles(QPainter& p) const
{
    const int outter_radius = m_squares.back().outter_radius;
    p.drawEllipse({0, 0}, outter_radius, outter_radius);
    p.drawEllipse({0, 0}, 3 * outter_radius / 4, 3 * outter_radius / 4);
    p.drawEllipse({0, 0}, outter_radius / 2, outter_radius / 2);
    p.drawEllipse({0, 0}, outter_radius / 4, outter_radius / 4);
}

void BoardWidget::drawLines(QPainter& p) const
{
    auto it = begin(m_squares);
    std::advance(it, 1);
    for(; it != end(m_squares); ++it)
    {
        p.drawLine(QLineF(toPoint({it->inner_radius, it->min_angle}), toPoint({it->outter_radius, it->min_angle})));
        p.drawLine(QLineF(toPoint({it->inner_radius, it->max_angle}), toPoint({it->outter_radius, it->max_angle})));
    }
}

void BoardWidget::drawMaxmimumsInSquares(QPainter& p) const
{
    const double dot_size = 4;
    p.save();
    p.setBrush(Qt::black);
    // inner circle
    const auto dist = m_squares.back().outter_radius / 16;
    p.drawEllipse(QPointF(dist, dist), dot_size, dot_size);
    p.drawEllipse(QPointF(dist, -dist), dot_size, dot_size);
    p.drawEllipse(QPointF(-dist, dist), dot_size, dot_size);
    p.drawEllipse(QPointF(-dist, -dist), dot_size, dot_size);

    for(const auto square_id : {9, 11, 13, 15}) // third row
    {
        const auto& square = m_squares[square_id];
        const auto angle = (square.max_angle + square.min_angle) / 2.;
        const auto min_dist = square.inner_radius;
        const auto max_dist = square.outter_radius;
        p.drawEllipse(toPoint({(max_dist - min_dist) / 3. + min_dist, angle}), dot_size, dot_size);
        p.drawEllipse(toPoint({2 * (max_dist - min_dist) / 3. + min_dist, angle}), dot_size, dot_size);
        p.drawEllipse(toPoint({(max_dist - min_dist) / 2. + min_dist, angle + PI / 5. / 8.}), dot_size, dot_size);
        p.drawEllipse(toPoint({(max_dist - min_dist) / 2. + min_dist, angle - PI / 5. / 8.}), dot_size, dot_size);
    }
    for(const auto square_id : {17, 19, 21, 23}) // fourth row
    {
        const auto& square = m_squares[square_id];
        const auto angle = (square.max_angle + square.min_angle) / 2.;
        const auto min_dist = square.inner_radius;
        const auto max_dist = square.outter_radius;
        p.drawEllipse(toPoint({(max_dist - min_dist) / 3. + min_dist, angle}), dot_size, dot_size);
        p.drawEllipse(toPoint({2 * (max_dist - min_dist) / 3. + min_dist, angle}), dot_size, dot_size);
    }
    p.restore();
}

void BoardWidget::drawCurrentSquare(QPainter& p) const
{
    if(!m_current_square) return;
    const auto& square = m_squares[*m_current_square];
    p.save();
    p.setPen(Qt::NoPen);
    p.setBrush(isSquarePlayable(*m_current_square) ? Qt::green : Qt::red);
    QPainterPath pp;
    pp.moveTo(toPoint({square.inner_radius, square.min_angle}));
    pp.lineTo(toPoint({square.outter_radius, square.min_angle}));
    pp.arcTo(
        {QPointF(-square.outter_radius, -square.outter_radius), QPointF(square.outter_radius, square.outter_radius)},
        toDegrees(transformAngle(square.min_angle)), toDegrees(square.min_angle - square.max_angle));
    pp.lineTo(toPoint({square.inner_radius, square.max_angle}));
    pp.arcTo({QPointF(-square.inner_radius, -square.inner_radius), QPointF(square.inner_radius, square.inner_radius)},
             toDegrees(transformAngle(square.max_angle)), toDegrees(square.max_angle - square.min_angle));

    p.drawPath(pp);
    p.restore();
}

void BoardWidget::drawStones(QPainter& p) const
{
    p.setPen(Qt::green);
    for(const auto& square : m_squares)
    {
        const auto radius = square.inner_radius  == 0 ? 0 : (square.outter_radius + square.inner_radius) / 2;
        const PolarPoint center{(square.outter_radius + square.inner_radius)/2, (square.max_angle + square.min_angle) / 2. };
        const auto size = (square.outter_radius - square.inner_radius) / 3;
        const auto r_max = center.radius + size / 2;
        const auto r_min = center.radius - size / 2;
        const auto stone_size = size / 2;
        p.drawEllipse(toPoint({r_min, center.angle}), stone_size, stone_size);
        p.drawEllipse(toPoint({r_max, center.angle}), stone_size, stone_size);
    }
}

boost::optional<Square> BoardWidget::findSquare(const PolarPoint& p) const
{

    for(std::size_t i = 0; i < m_squares.size(); i++)
    {
        const auto& s = m_squares[i];
        if(p.radius < s.inner_radius || p.radius > s.outter_radius) continue;
        if(p.angle < s.min_angle || p.angle > s.max_angle) continue;
        return Square(i);
    }
    return boost::none;
}

bool BoardWidget::isSquarePlayable(const Square square) const
{
    const auto move = buildMoveForSquare(square);
    return m_game.currentState().placeStone(move).has_value();
}

Move BoardWidget::buildMoveForSquare(const Square square) const
{
    return {square, m_game.currentPlayer(), 1};
}

boost::optional<Square> BoardWidget::mousePosToSquare(const QPoint& mouse_pos) const
{
    const auto pos = mouse_pos - QPoint(width(), height()) / 2;
    const auto radius = std::sqrt(QPointF::dotProduct(pos, pos));
    auto angle = std::atan2(pos.x(), -pos.y()) * radians;
    auto res = findSquare({radius, angle});
    if(!res) res = findSquare({radius, angle + 2. * PI});
    return res;
}

} // Aronda
