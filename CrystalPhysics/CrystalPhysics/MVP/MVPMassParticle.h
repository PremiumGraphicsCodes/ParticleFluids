#pragma once

#include "../../../Crystal/Math/Vector3d.h"
#include "../../../Crystal/Shape/IParticle.h"

namespace Crystal {
	namespace Physics {
		class MVPVolumeParticle;

class MVPMassParticle : public Shape::IParticle
{
public:
	MVPMassParticle(MVPVolumeParticle* parent, const Math::Vector3df& point, const float mass);

	Math::Vector3dd getPosition() const override;

	Math::Vector3df getVelocity() const;

	MVPVolumeParticle* getParent() { return parent; }

	void updatePosition();

	float getMass() const { return mass; }

	void setPressure(const float p) { this->pressure = p; }

	float getPressure() const { return pressure; }

	void setPressureCoe(const float c) { this->pressureCoe = c; }

	float getPressureCoe() const { return this->pressureCoe; }

	void setViscosityCoe(const float v) { this->viscosityCoe = v; }

	float getViscosityCoe() const { return viscosityCoe; }


	Math::Vector3df position;

private:
	MVPVolumeParticle* parent;
	Math::Vector3df vector;
	float mass;
	float pressure;
	float pressureCoe;
	float viscosityCoe;
};

	}
}