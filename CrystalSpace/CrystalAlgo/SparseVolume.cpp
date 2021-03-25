#include "SparseVolume.h"

using namespace Crystal::Math;
using namespace Crystal::Space;

Vector3dd SparseVolume::getPositionAt(const std::array<int, 3>& index) const
{
	const auto u = index[0] / static_cast<double>(resolutions[0]);
	const auto v = index[1] / static_cast<double>(resolutions[1]);
	const auto w = index[1] / static_cast<double>(resolutions[2]);

	return boundingBox.getPosition(u, v, w);
}

void SparseVolume::createNode(const std::array<int, 3>& index)
{
	const auto pos = getPositionAt(index);
	nodes[index] = new SparseVolumeNode(pos);
}
