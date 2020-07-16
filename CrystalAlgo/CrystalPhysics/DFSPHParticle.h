#pragma once

#include "../../Crystal/Shape/IPoint.h"
#include "SPHKernel.h"

namespace Crystal {
	namespace Physics {
		class SPHConstant;

class DFSPHParticle : public Shape::IPoint
{
public:
	DFSPHParticle(const Math::Vector3dd& position, const double radius, SPHConstant* constant) :
		position(position),
		velocity(0,0,0),
		radius(radius),
		constant(constant),
		density(0.0),
		alpha(0.0)
	{}

	Math::Vector3dd getPosition() const override { return position; }

	Math::Vector3dd getVelocity() const { return velocity; }

	double getRadius() const { return radius; }

	void addNeighbor(DFSPHParticle* neighbor) { this->neighbors.push_back( neighbor ); }

	void clearNeighbors() { this->neighbors.clear(); }

	std::vector<DFSPHParticle*> getNeighbors() const { return neighbors; }

	double getMass() const;

	void calculateDensity();

	void calculateAlpha();

	double calculateDpDt();

	void calculateVelocityInDivergenceError();

	void calculateVelocityInDensityError();

	Math::Vector3dd force;
	Math::Vector3dd velocity;
	Math::Vector3dd position;

private:
	const double radius;
	std::vector<DFSPHParticle*> neighbors;
	SPHKernel* kernel;
	SPHConstant* constant;
	double density;
	double alpha;
	double dpdt;
};
	}
}