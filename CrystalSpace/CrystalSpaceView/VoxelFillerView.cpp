#include "VoxelFillerView.h"

#include "../CrystalSpace/VoxelFiller.h"

#include "../../Crystal/Scene/VoxelScene.h"

#include <memory>

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Graphics;
using namespace Crystal::Scene;
using namespace Crystal::Space;
using namespace Crystal::UI;

VoxelFillerView::VoxelFillerView(const std::string& name, World* model, Canvas* canvas) :
	IOkCancelView(name, model, canvas)
{
}

void VoxelFillerView::onOk()
{
	const Box3d box(Vector3dd(0, 0, 0), Vector3dd(10, 10, 10));
	std::array<size_t, 3> res = { 10,10,10 };
	auto voxel = std::make_unique<Volume<bool>>(box, res);
	const double radius = 5.0;
	const Vector3dd center(5, 5, 5);
	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 10; ++j) {
			for (int k = 0; k < 10; ++k) {
				if(i == 3 || i == 7) {
					voxel->setValue(i, j, k, true);
				}
			}
		}
	}

	VoxelFiller filler;
	auto newVoxel = filler.createFilled(*voxel);
	auto vv = std::make_unique<Volume<bool>>(newVoxel.getBoundingBox(), newVoxel.getNodes());

	auto scene = new VoxelScene(getWorld()->getNextSceneId(), "Voxelized", std::move(vv));
	getWorld()->getScenes()->addScene(scene);

	auto presenter = scene->getPresenter();
	presenter->createView(getWorld()->getRenderer(), *getWorld()->getGLFactory());
}