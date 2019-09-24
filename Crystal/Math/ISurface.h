#pragma once

#include "Vector3d.h"

namespace Crystal {
	namespace Math {

class ISurface
{
public:
	virtual ~ISurface() = default;

	virtual Vector3dd getPosition(const double u, const double v) const = 0;
};

	}
}
