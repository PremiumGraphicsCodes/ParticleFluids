#include "SparseVolumeScene.h"

using namespace Crystal::Math;
using namespace Crystal::Space;

SparseVolumeScene::SparseVolumeScene(const int id, const std::string& name, const Box3d& bb, const std::array<int, 3>& resolutions) :
	boundingBox(bb),
	resolutions(resolutions)
{}

void SparseVolumeScene::createNode(const std::array<int, 3>& index)
{
	const auto pos = getPositionAt(index);
	nodes[index] = new SparseVolumeNode(pos);
}

Vector3dd SparseVolumeScene::getPositionAt(const std::array<int, 3>& index) const
{
	const auto u = index[0] / static_cast<double>(resolutions[0]);
	const auto v = index[1] / static_cast<double>(resolutions[1]);
	const auto w = index[1] / static_cast<double>(resolutions[2]);

	return boundingBox.getPosition(u, v, w);
}
