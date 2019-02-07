#pragma once

#include "Vector3d.h"

namespace Crystal {
	namespace Math {

class Quad3d
{
public:
	Quad3d(const Vector3dd& origin, const Vector3dd& uvec, const Vector3dd& vvec) :
		origin(origin),
		uvec(uvec),
		vvec(vvec)
	{
	}

	Vector3dd getPosition(const double u, const double v) const
	{
		return origin + uvec * u + vvec * v;
	}

	Vector3dd getNormal() const
	{
		return glm::normalize( glm::cross(uvec, vvec) );
	}

private:
	Vector3dd origin;
	Vector3dd uvec;
	Vector3dd vvec;
};
	}
}