#pragma once

#include "KFMicroParticle.h"

#include <vector>
#include <list>

namespace Crystal {
	namespace Physics {
		class KFFluidScene;

class KFMacroParticle : public Shape::IParticle
{
public:
	KFMacroParticle(const float radius, const Math::Vector3dd& position);

	~KFMacroParticle();

	void distributePoints(const int unum, const int vnum, const int wnum, const float weight);

	void setPressureCoe(const float c);

	void setViscosityCoe(const float c);

	//KFFluidScene* getScene() { return scene; }

	void reset(bool resetMicro);

	void addSelfMicro(KFMicroParticle* mp) { this->points.push_back(mp); }

	void addMicro(KFMicroParticle* microParticle);

	void calculateDensity();

	void calculatePressure();

	void calculatePressureForce(const float relaxationCoe);

	void calculateViscosityForce();

	void calculateVorticity();

	void stepTime(const float dt);

	float getRadius() const { return radius; }

	std::vector<KFMicroParticle*> getPoints() { return points; }

	Math::Vector3dd getPosition() const override { return position; }

	Math::Vector3df getPositionf() const { return position; }

	Math::Vector3dd getVelocity() const { return velocity; }

	void addForce(const Math::Vector3dd& force) { this->force += force; }

	//void addBoundaryCount(const int count) { this->boundaryCount += count; }

	float getDensity() const;

	void updateMicros();

	//void addMicroCount(int count) { this->microCount+=count; }

	void updateInnerPoints();

	float getSelfMass() { return restMass; }

	void setVelocity(const Math::Vector3df& velocity) { this->velocity = velocity; }

private:
	float radius;
	std::vector<KFMicroParticle*> points;
	std::vector<KFMicroParticle*> innerPoints;
	std::vector<KFMicroParticle*> microPoints;
	Math::Vector3df force;
	Math::Vector3df position;
	Math::Vector3df velocity;
	Math::Vector3df vorticity;
	//KFFluidScene* scene;

	//float selfMass;
	float restMass;
	float density;
	float pressure;
};

	}
}