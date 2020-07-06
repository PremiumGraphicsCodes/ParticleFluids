#pragma once

#include "../../Crystal/Math/Vector3d.h"
#include "../../Crystal/Shape/IPoint.h"

namespace Crystal {
	namespace Physics {
		class MacroParticle;

class MicroParticle : public Shape::IPoint
{
public:
	MicroParticle(MacroParticle* parent, const Math::Vector3dd& point) :
		parent(parent),
		vector(point)
	{
		updatePosition();
	}

	Math::Vector3dd getPosition() const override;

	Math::Vector3dd getVelocity() const;

	MacroParticle* getParent() { return parent; }

	void updatePosition();

private:
	MacroParticle* parent;
	Math::Vector3dd position;
	Math::Vector3dd vector;
};

	}
}
