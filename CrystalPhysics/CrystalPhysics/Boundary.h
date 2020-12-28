#pragma once

#include "../../Crystal/Shape/Particle.h"

#include "../../Crystal/Util/UnCopyable.h"

namespace Crystal {
	namespace Shape {
		class PolygonMesh;
	}
	namespace Physics {

class BoundaryAttr : public Shape::IParticleAttribute
{
public:
	explicit BoundaryAttr(Math::Vector3dd normal) :
		normal(normal)
	{
	}

	Math::Vector3dd normal;
};

class Boundary //: private UnCopyable
{
public:
	void build(const Shape::PolygonMesh& mesh, const double divideLength);

	std::vector<Shape::Particle<BoundaryAttr>> getParticles() const { return positionWithNormal; }

private:
	std::vector<Shape::Particle<BoundaryAttr>> positionWithNormal;
};
	}
}