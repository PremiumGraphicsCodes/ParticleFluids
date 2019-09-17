#pragma once

#include "Vector3d.h"

namespace Crystal {
	namespace Math {

class ICurveU
{
public:
	virtual ~ICurveU() = default;

	virtual Vector3dd getPosition(const double u) const = 0;
};

	}
}
