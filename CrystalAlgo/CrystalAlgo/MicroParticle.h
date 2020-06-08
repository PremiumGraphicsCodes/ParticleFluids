#pragma once

#include "../../Crystal/Math/Vector3d.h"
#include "../../Crystal/Shape/IPoint.h"

namespace Crystal {
	namespace Algo {
		namespace Physics {
			class MacroParticle;

class MicroParticle : public Shape::IPoint
{
public:
	MicroParticle(MacroParticle* parent, const Math::Vector3dd& point) :
		parent(parent),
		vector(point)
	{}

	Math::Vector3dd getPosition() const override;

	Math::Vector3dd getVelocity() const;

	void move(const Math::Vector3dd& v) override {};

	void transform(const Math::Matrix3dd& m) override {};

	void transform(const Math::Matrix4dd& m) override {};

private:
	MacroParticle* parent;
	Math::Vector3dd vector;
};

		}
	}
}
