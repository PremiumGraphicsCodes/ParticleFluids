#include "VoxelScene.h"

//#include "SparseVolumePresenter.h"

using namespace Crystal::Math;
using namespace Crystal::Space;

VoxelScene::VoxelScene(const int id, const std::string& name, std::unique_ptr<Voxel> shape) :
	shape(std::move(shape))
{
	//presenter = std::make_unique<SparseVolumePresenter>(this);
}

Box3d VoxelScene::getBoundingBox() const
{
	return shape->getBoundingBox();
}