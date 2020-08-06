#pragma once

#include "../../Crystal/Shape/Particle.h"

#include "../../Crystal/Util/UnCopyable.h"

namespace Crystal {
	namespace Shape {
		class PolygonMesh;
	}
	namespace Physics {

class Boundary : private UnCopyable
{
public:
	void build(const Shape::PolygonMesh& mesh, const double divideLength);

	std::vector<Shape::Particle<Math::Vector3dd>> getParticles() const { return positionWithNormal; }

private:
	std::vector<Shape::Particle<Math::Vector3dd>> positionWithNormal;
};
	}
}