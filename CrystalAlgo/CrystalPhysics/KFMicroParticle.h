#pragma once

#include "../../Crystal/Math/Vector3d.h"
#include "../../Crystal/Shape/IParticle.h"

namespace Crystal {
	namespace Physics {
		class KFMacroParticle;

class KFMicroParticle : public Shape::IParticle
{
public:
	KFMicroParticle(KFMacroParticle* parent, const Math::Vector3df& point, const float mass) :
		parent(parent),
		vector(point),
		mass(mass)
	{
		updatePosition();
	}

	Math::Vector3dd getPosition() const override;

	Math::Vector3df getVelocity() const;

	KFMacroParticle* getParent() { return parent; }

	void updatePosition();

	float getMass() const { return mass; }

	Math::Vector3df position;

private:
	KFMacroParticle* parent;
	Math::Vector3df vector;
	float mass;
};

	}
}
