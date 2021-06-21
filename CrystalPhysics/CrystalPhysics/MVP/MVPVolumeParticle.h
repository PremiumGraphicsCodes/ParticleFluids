#pragma once

#include "MVPMassParticle.h"

#include <vector>
#include <list>

namespace Crystal {
	namespace Physics {
		class MVPFluidScene;

class MVPVolumeParticle : public Shape::IParticle
{
public:
	MVPVolumeParticle(const float radius, const Math::Vector3dd& position);

	~MVPVolumeParticle();

	void setPressureCoe(const float c);

	void setViscosityCoe(const float c);

	//KFFluidScene* getScene() { return scene; }

	void reset(bool resetMicro);

	void addNeighbor(MVPVolumeParticle* neighbor) { this->neighbors.push_back(neighbor); }

	void addMassParticle(MVPMassParticle* massParticle) { this->massParticles.push_back(massParticle); }

	void calculateDensity();

	//void calculatePressure();

	void calculatePressureForce(const float relaxationCoe);

	void calculateViscosityForce();

	void calculateVorticity();

	void stepTime(const float dt);

	float getRadius() const { return radius; }

	std::vector<MVPMassParticle*> getPoints() { return massParticles; }

	Math::Vector3dd getPosition() const override { return position; }

	Math::Vector3df getPositionf() const { return position; }

	Math::Vector3df getVelocity() const { return velocity; }

	Math::Vector3df getVorticity() const { return vorticity; }

	void addForce(const Math::Vector3dd& force) { this->force += force; }

	float getDensity() const;

	void updateMicros();

	void updateInnerPoints();

	float getSelfMass() { return restMass; }

	void setVelocity(const Math::Vector3df& velocity) { this->velocity = velocity; }

	void setRestMass(const float m) { this->restMass = m; }

private:
	float pressureCoe;
	float radius;
	std::vector<MVPMassParticle*> massParticles;
	std::vector<MVPMassParticle*> innerPoints;
	std::vector<MVPVolumeParticle*> neighbors;
	Math::Vector3df force;
	Math::Vector3df position;
	Math::Vector3df velocity;
	Math::Vector3df vorticity;
	float restMass;
	float density;
	float pressure;
};

	}
}