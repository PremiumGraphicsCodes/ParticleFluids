#pragma once

#include "Vector3d.h"

namespace Crystal {
	namespace Math {

class ISurface3d
{
public:
	virtual ~ISurface3d() = default;

	virtual Vector3dd getPosition(const double u, const double v) const = 0;

	virtual Vector3dd getNormal(const double u, const double v) const = 0;
};

	}
}
