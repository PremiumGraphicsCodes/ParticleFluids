#pragma once

#include "../../Crystal/Math/Vector3d.h"
#include "../../Crystal/Shape/IPoint.h"

namespace Crystal {
	namespace Algo {
		namespace Physics {

class MicroParticle : public Shape::IPoint
{
public:
	explicit MicroParticle(const Math::Vector3dd& point) :
		vector(point)
	{}

	Math::Vector3dd getPosition() const override { return vector; }

	void move(const Math::Vector3dd& v) override {};

	void transform(const Math::Matrix3dd& m) override {};

	void transform(const Math::Matrix4dd& m) override {};

private:
	Math::Vector3dd vector;
};

		}
	}
}
