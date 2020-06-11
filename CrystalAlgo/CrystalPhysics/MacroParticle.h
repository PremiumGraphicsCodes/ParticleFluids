#pragma once

#include "MicroParticle.h"

#include <vector>
#include <list>

namespace Crystal {
	namespace Algo {
		namespace Physics {

class MacroParticle
{
public:
	MacroParticle(const double radius, const Math::Vector3dd& position);

	void distributePoints(const int unum, const int vnum);

	void distributePoints(const int unum, const int vnum, const int wnum);

	//void calculateDensity();

	void reset() { this->force = Math::Vector3dd(0, 0, 0); }

	void calculatePressure();

	void calculateViscosity();

	void stepTime(double dt);

	double getRadius() const { return radius; }

	std::vector<MicroParticle*> getPoints() { return points; }

	void setInnerPoints(const std::list<MicroParticle*>& inners) { this->innerPoints = inners; }

	Math::Vector3dd getPosition() const { return position; }

	Math::Vector3dd getVelocity() const { return velocity; }

	void addForce(const Math::Vector3dd& force) { this->force += force; }

	void setStatic(const bool isStatic) { this->isStatic = isStatic; }

private:
	double radius;
	std::vector<MicroParticle*> points;
	std::list<MicroParticle*> innerPoints;
	Math::Vector3dd force;
	Math::Vector3dd position;
	Math::Vector3dd velocity;
	int preCount;
	//double density;
	bool isStatic = false;
};

		}
	}
}