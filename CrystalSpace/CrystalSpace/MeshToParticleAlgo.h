#pragma once

#include "../../Crystal/Shape/PolygonMesh.h"

namespace Crystal {
	namespace Space {

class MeshToParticleAlgo
{
public:
	//MeshToParticleAlgo();

	void subdivide(const Shape::PolygonMesh& mesh, const double divideLength);

	void subdivide(const Math::Triangle3d& triangle, const double divideLength);

	std::vector<Math::Vector3dd> getPositions() const { return positions; }

	std::vector<Math::Vector3dd> getNormals() const { return normals; }

private:
	std::vector<Math::Vector3dd> positions;

	std::vector<Math::Vector3dd> normals;
	
};
	}
}