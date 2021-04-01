#include "SparseVolumeScene.h"

#include "SparseVolumePresenter.h"

using namespace Crystal::Math;
using namespace Crystal::Space;

SparseVolumeScene::SparseVolumeScene(const int id, const std::string& name, std::unique_ptr<SparseVolume> shape) :
	shape(std::move(shape))
{
	presenter = std::make_unique<SparseVolumePresenter>(this);
}

Box3d SparseVolumeScene::getBoundingBox() const
{
	return shape->getBoundingBox();
}