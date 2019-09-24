#pragma once

#include "Vector2d.h"
#include "Vector3d.h"

namespace Crystal {
	namespace Math {

class IVolume
{
public:
	virtual ~IVolume() = default;

	virtual Vector3dd getPosition(const Math::Vector3dd& p) const = 0;

	virtual Vector3dd getNormal(const Math::Vector2dd& p) const
	{
		return getPosition(Vector3dd(p, 1.0) - Vector3dd(p, 0.0));

	}
};

	}
}
