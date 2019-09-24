#pragma once

#include "Vector3d.h"

namespace Crystal {
	namespace Math {

class ICurve
{
public:
	virtual ~ICurve() = default;

	virtual Vector3dd getPosition(const double u) const = 0;
};

	}
}
