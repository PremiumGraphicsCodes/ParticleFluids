#pragma once

#include "../../Crystal/Math/Vector3d.h"
#include "../../Crystal/Shape/IPoint.h"

namespace Crystal {
	namespace Physics {
		class KFMacroParticle;

class MicroParticle : public Shape::IPoint
{
public:
	MicroParticle(KFMacroParticle* parent, const Math::Vector3df& point, const float weight) :
		parent(parent),
		vector(point),
		weight(weight)
	{
		updatePosition();
	}

	Math::Vector3dd getPosition() const override;

	Math::Vector3df getVelocity() const;

	KFMacroParticle* getParent() { return parent; }

	void updatePosition();

	float getWeight() const { return weight; }

private:
	KFMacroParticle* parent;
	Math::Vector3df position;
	Math::Vector3df vector;
	float weight;
};

	}
}
