#include "Circle3d.h"

#include "Tolerance.h"
#include <cmath>

using namespace Crystal::Math;

Circle3d::Circle3d() :
	center(Vector3dd(0,0,0)),
	uvec(Vector3dd(1,0,0)),
	vvec(Vector3dd(0,1,0))
{}

Circle3d::Circle3d(const Vector3dd& center, const Vector3dd& uvec, const Vector3dd& vvec) :
	center(center),
	uvec(uvec),
	vvec(vvec)
{}

Vector3dd Circle3d::getPosition(const double u) const
{
	const auto uu = u * 2.0 * PI;
	return center + ::cos(uu) * uvec + ::sin(uu) * vvec;
}

Vector3dd Circle3d::getNormal() const
{
	return glm::normalize( glm::cross(uvec, vvec) );
}

