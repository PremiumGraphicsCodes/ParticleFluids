#pragma once

#include <array>
#include <vector>

#include "../../Crystal/Math/Vector3d.h"
#include "../../Crystal/Math/Box3d.h"
#include "../../Crystal/Util/UnCopyable.h"

namespace Crystal {
	namespace Shape {
		class IParticle;
	}
	namespace Algo {

class Octree //: private UnCopyable
{
public:
	Octree() {};

	Octree(const Math::Box3d& space);

	void add(Shape::IParticle* particle);

	std::vector<Octree> createChildren() const;

	std::vector<Octree> createChildren(const int depth) const;

	bool isEmpty() const;

	bool equals(const Octree& rhs, const double tolerance) const;

	std::vector<Shape::IParticle*> getParticles() const { return particles; }

private:
	std::vector<Shape::IParticle*> particles;
	Math::Box3d space;
};

	}
}