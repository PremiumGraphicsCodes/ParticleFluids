#pragma once

#include "../Math/Vector3d.h"
#include "../Math/Matrix3d.h"
#include "../Math/Matrix4d.h"

namespace Crystal {
	namespace Shape {

class IParticle
{
public:
	~IParticle()
	{}

	virtual Math::Vector3dd getPosition() const = 0;
};

	}
}