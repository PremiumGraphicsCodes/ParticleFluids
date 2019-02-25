#pragma once

#include "Vector3d.h"
#include "ICurve3d.h"

namespace Crystal {
	namespace Math {

class Torus3d : public ICurve3d
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

	double getBigRadius() const { return R; }

	double getSmallRadius() const { return r; }

	Vector3dd getPosition(const double u, const double v) const override
	{
		const auto t = u * 2.0 * Tolerance<double>::getPI();
		const auto p = v * 2.0 * Tolerance<double>::getPI();
		const auto x = R * ::cos(t) + r * ::cos(p) * ::cos(t);
		const auto y = R * ::sin(t) + r * ::cos(p) * ::sin(t);
		const auto z = r * ::sin(p);
		return center + Vector3dd(x, y, z);
	}

private:
	Vector3dd center;
	double R;
	double r;
};
	}
}