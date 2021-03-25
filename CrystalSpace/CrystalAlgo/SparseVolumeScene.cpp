#include "SparseVolumeScene.h"

using namespace Crystal::Math;
using namespace Crystal::Space;

SparseVolumeScene::SparseVolumeScene(const int id, const std::string& name, const Box3d& bb) :
	boundingBox(bb)
{}

/*
void SparseVolumeScene::createNode(const std::array<int, 3>& index)
{
	nodes[index] = new SparseVolumeNode();
}
*/
