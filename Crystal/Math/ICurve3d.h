#pragma once

#include "Vector3d.h"

namespace Crystal {
	namespace Math {

class ICurve3d
{
public:
	virtual ~ICurve3d() = default;

	virtual Vector3dd getPosition(const double u, const double v) const = 0;
};

	}
}
