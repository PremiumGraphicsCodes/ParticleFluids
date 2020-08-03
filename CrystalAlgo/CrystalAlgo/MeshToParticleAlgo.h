#pragma once

#include "../../Crystal/Shape/PolygonMesh.h"

namespace Crystal {
	namespace Algo {

class MeshToParticleAlgo
{
public:
	//MeshToParticleAlgo();

	void subdivide(const Shape::PolygonMesh& mesh, const double divideLength);

	std::vector<Math::Vector3dd> getPositions() const { return positions; }

private:
	void subdivide(const Math::Triangle3d& triangle, const double divideLength);

	std::vector<Math::Vector3dd> positions;
	
};
	}
}