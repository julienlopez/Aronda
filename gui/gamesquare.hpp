#pragma once

#include <vector>

#include <boost/units/quantity.hpp>
#include <boost/units/systems/si/plane_angle.hpp>

namespace Aronda
{

using Angle_t = boost::units::quantity<boost::units::si::plane_angle>;

struct GameSquare
{
    double inner_radius;
    double outter_radius;
    Angle_t min_angle;
    Angle_t max_angle;
};

using GameSquareContainer_t = std::vector<GameSquare>;

GameSquareContainer_t buildSquares(const double outter_radius);

const auto PI = 3.14159265359 * boost::units::si::radians;
}
