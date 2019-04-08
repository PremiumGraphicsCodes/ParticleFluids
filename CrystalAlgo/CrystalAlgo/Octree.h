#pragma once

#include <array>
#include <vector>

#include "../../Crystal/Math/Vector3d.h"
#include "../../Crystal/Math/Box3d.h"

namespace Crystal {
	namespace Algo {
		class IParticle;

class Octree
{
public:
	Octree() {};

	Octree(const Math::Box3d& space);

	void add(IParticle* particle) { this->particles.push_back(particle); }

	std::vector<Octree> createChildren() const;

	std::vector<Octree> createChildren(const int depth) const;

	bool isEmpty() const;

	bool equals(const Octree& rhs, const double tolerance) const;

	std::vector<IParticle*> getParticles() const { return particles; }

private:
	std::vector<IParticle*> particles;
	Math::Box3d space;
};

	}
}