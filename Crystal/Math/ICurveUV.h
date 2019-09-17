#pragma once

#include "Vector3d.h"

namespace Crystal {
	namespace Math {

class ICurveUV
{
public:
	virtual ~ICurveUV() = default;

	virtual Vector3dd getPosition(const double u, const double v) const = 0;
};

	}
}
