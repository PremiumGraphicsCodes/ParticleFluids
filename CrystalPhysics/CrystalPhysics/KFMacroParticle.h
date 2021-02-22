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

	void setScene(KFFluidScene* scene);

	KFFluidScene* getScene() { return scene; }

	//void calculateDensity();

	void reset(bool resetMicro);

	void addSelfMicro(KFMicroParticle* mp) { this->points.push_back(mp); }

	void addMicro(KFMicroParticle* microParticle);

	//void calculatePressure();

	void calculatePressureForce(const float relaxationCoe);

	void calculateViscosityForce();

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

	float getSelfMass() { return selfMass; }

private:
	float radius;
	std::vector<KFMicroParticle*> points;
	std::vector<KFMicroParticle*> innerPoints;
	std::vector<KFMicroParticle*> microPoints;
	Math::Vector3df force;
	Math::Vector3df position;
	Math::Vector3df velocity;
	KFFluidScene* scene;

	float selfMass;
	float totalMass;
	float pressure;
};

	}
}