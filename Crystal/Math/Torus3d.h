#pragma once

#include "Vector3d.h"

namespace Crystal {
	namespace Math {

class Torus3d
{
public:
	Torus3d():
		center(0,0,0),
		R(1.0),
		r(0.5)
	{}

	Torus3d(const Math::Vector3dd& center, const double R, const double r) :
		center(center),
		R(R),
		r(r)
	{}

	Vector3dd getCenter() const { return center; }

	double getR() const { return R; }

	double getr() const { return r; }

	Vector3dd getPosition(const double t, const double p) const {
		const auto tt = t * 2.0 * Tolerance<double>::getPI();
		const auto pp = p * 2.0 * Tolerance<double>::getPI();
		const auto x = R * ::cos(tt) + r * ::cos(pp) * ::cos(tt);
		const auto y = R * ::sin(tt) + r * ::cos(pp) * ::sin(tt);
		const auto z = r * ::sin(pp);
		return Vector3dd(x, y, z);
	}

private:
	Vector3dd center;
	double R;
	double r;
};
	}
}