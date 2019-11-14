#pragma once

#include "Vector2d.h"
#include "Vector3d.h"

namespace Crystal {
	namespace Math {

class IVolume3d
{
public:
	virtual ~IVolume3d() = default;

	virtual Vector3dd getPosition(const double u, const double v, const double w) const = 0;

	virtual bool isInside(const Math::Vector3dd& position) const = 0;

};

	}
}
