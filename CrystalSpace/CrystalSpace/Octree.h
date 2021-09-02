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
	namespace Space {

class Octree //: private UnCopyable
{
public:
	Octree() {};

	explicit Octree(const Math::Box3dd& space);

	void add(Shape::IParticle* particle);

	void createChildren() const;

	bool isEmpty() const;

	std::vector<Shape::IParticle*> getParticles() const { return particles; }

private:
	std::vector<Shape::IParticle*> particles;
	std::vector<Octree*> children;
	Math::Box3dd space;
};

	}
}