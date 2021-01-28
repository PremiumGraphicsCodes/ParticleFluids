#pragma once

#include "../../Crystal/Math/Vector3d.h"
#include "../../Crystal/Shape/IParticle.h"

namespace Crystal {
	namespace Physics {
		class KFMacroParticle;

class KFMicroParticle : public Shape::IParticle
{
public:
	KFMicroParticle(KFMacroParticle* parent, const Math::Vector3df& point, const float mass);

	Math::Vector3dd getPosition() const override;

	Math::Vector3df getVelocity() const;

	KFMacroParticle* getParent() { return parent; }

	void updatePosition();

	float getMass() const { return mass; }

	void setPressureCoe(const float p) { this->pressureCoe = p; }

	void setViscosityCoe(const float v) { this->viscosityCoe = v; }

	float getPressureCoe() const { return pressureCoe; }

	float getViscosityCoe() const { return viscosityCoe; }

	Math::Vector3df position;

private:
	KFMacroParticle* parent;
	Math::Vector3df vector;
	float mass;
	float pressureCoe;
	float viscosityCoe;
};

	}
}
