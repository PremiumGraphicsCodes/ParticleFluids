#pragma once

#include "../Math/Vector3d.h"
#include "../Math/Matrix3d.h"
#include "../Math/Matrix4d.h"

namespace Crystal {
	namespace Shape {

class IPoint
{
public:
	~IPoint()
	{}

	virtual Math::Vector3dd getPosition() const = 0;
};

	}
}