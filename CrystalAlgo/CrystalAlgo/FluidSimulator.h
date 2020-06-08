#pragma once

#include <vector>
#include <list>
#include "../../Crystal/Math/Vector3d.h"
#include "../../Crystal/Shape/IPoint.h"

namespace Crystal {
	namespace Algo {

class MicroPoint : public Shape::IPoint
{
	Math::Vector3dd vector;

};

class MacroParticle
{
public:
	explicit MacroParticle(const double radius) :
		radius(radius)
	{}

	void distributePoints(const int unum, const int vnum);

	void calculateDensity();

//	void calculatePressure();

//	void calculateViscosity();

//	void stepTime(double dt);

	double getRadius() const { return radius; }

	std::vector<MicroPoint*> getPoints() { return points; }

	void setInnerPoints(const std::list<Shape::IPoint*>& inners) { this->innerPoints; }

	Math::Vector3dd getPosition() const { return position; }

private:
	double radius;
	std::vector<MicroPoint*> points;
	std::list<Shape::IPoint*> innerPoints;
	Math::Vector3dd force;
	Math::Vector3dd position;
	Math::Vector3dd velocity;
};

class FluidSimulator
{
public:
	void addParticle(MacroParticle* particle) {
		this->particles.push_back(particle);
	}

	void simulate(const double dt);

private:
	void calculateDensity();

	void calculatePressure();

	void calculateViscosity();

private:
	std::list<MacroParticle*> particles;
};
	}
}