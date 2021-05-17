#include "MeshToParticleConverter.h"

#include "MeshToVoxelConverter.h"

#include "../../Crystal/Math/Triangle3d.h"
#include "../../Crystal/Math/Circle3d.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Space;

void MeshToParticleConverter::subdivide(const PolygonMesh& mesh, const double divideLength)
{
	MeshToVoxelConverter converter;
	converter.convert(mesh, divideLength);
	auto voxel = converter.toVoxel();
	auto nodes = voxel->getNodes();

	for (const auto& node : nodes) {
		positions.push_back( node.second->getPosition() );
	}
}
