#pragma once

#include "../Math/Vector3d.h"

namespace Crystal {
	namespace Math {

class Ray3d
{
public:
	Ray3d() :
		origin(0,0,0),
		direction(1,0,0)
	{
	}

	Vector3dd getOrigin() const { return origin; }

	Vector3dd getDirection() const { return direction; }

private:
	Vector3dd origin;
	Vector3dd direction;
};

	}
}