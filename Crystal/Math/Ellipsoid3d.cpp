#include "Ellipsoid3d.h"

#include "Box3d.h"

using namespace Crystal::Math;

Ellipsoid3d::Ellipsoid3d() :
	center(0,0,0),
	uvec(1,0,0),
	vvec(0,1,0),
	wvec(0,0,1)
{}

Ellipsoid3d::Ellipsoid3d(const Vector3dd& center, const Vector3dd& uvec, const Vector3dd& vvec, const Vector3dd& wvec) :
	center(center),
	uvec(uvec),
	vvec(vvec),
	wvec(wvec)
{
}

Vector3dd Ellipsoid3d::getPosition(const double u, const double v, const double w) const
{
	const auto uu = u * 2.0 * PI;
	auto x = uvec * ::cos(uu);
	const auto vv = v * 2.0 * PI;
	auto y = vvec * ::cos(vv);
	const auto ww = w * 2.0 * PI;
	auto z = wvec * ::cos(ww);	
	return x + y + z;
}

bool Ellipsoid3d::isSame(const Ellipsoid3d& rhs, const double tolerance) const
{
	return
		areSame(center, rhs.center, tolerance) &&
		areSame(uvec, rhs.uvec, tolerance) &&
		areSame(vvec, rhs.vvec, tolerance) &&
		areSame(wvec, rhs.wvec, tolerance);
}

Box3d Ellipsoid3d::getBoundingBox() const
{
	Box3d bb(getPosition(0, 0, 0));
	bb.add(getPosition(1, 1, 1));
	return bb;
}