#pragma once

#include "../../Crystal/Shape/IPoint.h"
#include "SPHKernel.h"

namespace Crystal {
	namespace Physics {
		class SPHConstant;

class DFFluidParticle : public Shape::IPoint
{
public:
	DFFluidParticle(const Math::Vector3dd& position, const double radius, SPHConstant* constant) :
		position(position),
		radius(radius),
		constant(constant),
		density(0.0)
	{}

	Math::Vector3dd getPosition() const override { return position; }

	double getRadius() const { return radius; }

	void setNeighbors(const std::vector<DFFluidParticle*>& neighbors) { this->neighbors = neighbors; }

	double getMass() const;

	void addSelfDensity();

	void addDensity(const DFFluidParticle& rhs);

	void addDensity(const float distance, const float mass);

private:
	Math::Vector3dd position;
	const double radius;
	std::vector<DFFluidParticle*> neighbors;
	SPHKernel* kernel;
	SPHConstant* constant;
	double density;
};
	}
}