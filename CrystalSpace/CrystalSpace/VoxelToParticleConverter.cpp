#include "VoxelToParticleConverter.h"

#include "../../Crystal/Math/Triangle3d.h"
#include "../../Crystal/Math/Circle3d.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Space;

void VoxelToParticleConverter::convert(const SparseVoxel& voxel)
{
	const auto& nodes = voxel.getNodes();

	for (const auto& node : nodes) {
		positions.push_back(node.second->getPosition());
	}
}
