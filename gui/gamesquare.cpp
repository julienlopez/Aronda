#include "gamesquare.hpp"

#include "game.hpp"

#include <gsl/gsl_assert>

namespace Aronda
{

	using boost::units::si::radians;

	GameSquareContainer_t buildSquares(const double outter_radius)
	{
		GameSquareContainer_t res;
		res.push_back({ 0., outter_radius / 4., 0. * radians, 2. * PI });
		for (int i = 0; i < 8; i++) // second circle for the center
		{
			const auto angle = i / 4. * PI;
			res.push_back({ outter_radius / 4, outter_radius / 2, angle - PI / 0.8, angle + PI / 0.8 });
		}

		for(int i = 0; i < 8; i++) // third circle for the center
		{
			const auto angle = (i + 0.5) * PI / 4.;
			res.push_back({ outter_radius / 2, 3 * outter_radius / 4, angle - PI / 0.8, angle + PI / 0.8 });
		}

		for(int i = 0; i < 4; i++) // fourth circle for the center
		{
			const auto min_angle = (4 * i + 0.5) * PI / 8.;
			const auto max_angle = (4 * i - 0.5) * PI / 8.;
			res.push_back({ 3 * outter_radius / 4, outter_radius, min_angle, max_angle });
			res.push_back({ 3 * outter_radius / 4, outter_radius, max_angle, (4 * i + 1.5) * PI / 8. });
		}
		Ensures(res.size() == c_number_of_squares);
		return res;
	}

}
