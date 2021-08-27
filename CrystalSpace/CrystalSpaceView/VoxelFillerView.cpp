#include "VoxelFillerView.h"

#include "../CrystalSpace/VoxelFiller.h"

#include "../../Crystal/Scene/ParticleSystemScene.h"
#include "../../Crystal/Scene/PolygonMeshScene.h"

#include "../../Crystal/Shape/PolygonMeshBuilder.h"
#include "../../Crystal/Scene/VolumeScene.h"

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
	Crystal::Util::Array3d<bool> source(10, 10, 10);
	const double radius = 5.0;
	const Vector3dd center(5, 5, 5);
	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 10; ++j) {
			for (int k = 0; k < 10; ++k) {
				const auto p = Vector3dd(i, j, k);
				const auto distance = getDistance(center, p);
			}
		}
	}

	//VoxelFiller filler;
	//filler.fill()
	//voxelizer.voxelize(*mesh, divideLengthView.getValue());

	//auto scene = new VolumeScene(getWorld()->getNextSceneId(), "Voxelized", std::move(ps));
	//getWorld()->getScenes()->addScene(scene);

	//auto presenter = scene->getPresenter();
	//presenter->createView(getWorld()->getRenderer(), *getWorld()->getGLFactory());
}