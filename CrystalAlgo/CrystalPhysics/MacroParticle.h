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

	~MacroParticle();

	void distributePoints(const int unum, const int vnum);

	void distributePoints(const int unum, const int vnum, const int wnum);

	void setScene(KFFluidScene* scene) { this->scene = scene; }

	KFFluidScene* getScene() { return scene; }

	//void calculateDensity();

	void reset(bool resetMicro);

	void addSelfMicro(MicroParticle* mp) { this->points.push_back(mp); }

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

	void addBoundaryCount(const int count) { this->boundaryCount += count; }

	double getDensity() const;

	void updateMicros();

	//void addMicroCount(int count) { this->microCount+=count; }

	void updateInnerPoints();

private:
	double radius;
	std::vector<MicroParticle*> points;
	std::vector<MicroParticle*> innerPoints;
	std::vector<MicroParticle*> microPoints;
	Math::Vector3dd force;
	Math::Vector3dd position;
	Math::Vector3dd velocity;
	KFFluidScene* scene;
	int boundaryCount;

	//int microCount;
	int selfCount;
	//double density;
	bool isStatic = false;
};

	}
}