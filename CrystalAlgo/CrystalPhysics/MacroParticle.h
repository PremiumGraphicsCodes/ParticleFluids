#pragma once

#include "MicroParticle.h"

#include <vector>
#include <list>

namespace Crystal {
	namespace Physics {
		class KFFluidScene;

class MacroParticle : public Shape::IPoint
{
public:
	MacroParticle(const double radius, const Math::Vector3dd& position);

	void distributePoints(const int unum, const int vnum);

	void distributePoints(const int unum, const int vnum, const int wnum);

	void setScene(KFFluidScene* scene) { this->scene = scene; }

	KFFluidScene* getScene() { return scene; }

	//void calculateDensity();

	void reset();

	void addMicro(MicroParticle* microParticle);

	void calculatePressure(const double pressureCoe);

	void calculateViscosity(const double viscosityCoe);

	void stepTime(double dt);

	double getRadius() const { return radius; }

	std::vector<MicroParticle*> getPoints() { return points; }

	Math::Vector3dd getPosition() const override { return position; }

	Math::Vector3dd getVelocity() const { return velocity; }

	void addForce(const Math::Vector3dd& force) { this->force += force; }

	void setStatic(const bool isStatic) { this->isStatic = isStatic; }

	double getDensity() const;

	//void addMicroCount(int count) { this->microCount+=count; }

private:
	double radius;
	std::vector<MicroParticle*> points;
	std::list<MicroParticle*> microPoints;
	Math::Vector3dd force;
	Math::Vector3dd position;
	Math::Vector3dd velocity;
	KFFluidScene* scene;

	//int microCount;
	int selfCount;
	//double density;
	bool isStatic = false;
};

	}
}