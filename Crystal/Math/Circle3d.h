#pragma once

#include "ICurve3d.h"
#include "Vector3d.h"

namespace Crystal {
	namespace Math {

class Circle3d : public ICurve3d
{
public:
	Circle3d();

	Circle3d(const Vector3dd& center, const Vector3dd& uvec, const Vector3dd& vvec);

	Vector3dd getPosition(const double u) const;

	Vector3dd getNormal() const;

	Vector3dd getCenter() const { return center; }

	Vector3dd getUVec() const { return uvec; }

	Vector3dd getVVec() const { return vvec; }

private:
	Vector3dd center;
	Vector3dd uvec;
	Vector3dd vvec;
};
	}
}