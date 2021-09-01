#include "VoxelizerView.h"

#include "../CrystalSpace/Voxelizer.h"
#include "../../Crystal/Scene/VoxelScene.h"

#include "../../Crystal/Scene/ParticleSystemScene.h"
#include "../../Crystal/Scene/PolygonMeshScene.h"

#include "../../Crystal/Shape/PolygonMeshBuilder.h"
#include "../../Crystal/Math/Sphere3d.h"

//#include "../../Crystal/IO/TEXT"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Graphics;
using namespace Crystal::Scene;
using namespace Crystal::Space;
using namespace Crystal::UI;

VoxelizerView::VoxelizerView(const std::string& name, World* model, Canvas* canvas) :
	IOkCancelView(name, model, canvas),
	divideLengthView("DivideLength", 1.0)
{
	//toPointsButton.setFunction([=]() { toPoints(); });
	//toVoxelButton.setFunction([=]() { toVolume(); });

	//add(&toPointsButton);
	//add(&toVoxelButton);

	add(&divideLengthView);
}

#include <fstream>

void VoxelizerView::onOk()
{
	PolygonMeshBuilder builder;
	const Box3d box(Vector3dd(2, 2, 2), Vector3dd(8, 8, 8));
	builder.add(box, 2, 2, 2);
	//const Sphere3dd sphere(Vector3dd(0, 0, 0), 5);
	//builder.add(sphere, 32, 32);
	auto mesh = builder.build();

	Voxelizer voxelizer;
	voxelizer.voxelize(*mesh, 1.0);
	//voxelizer.fill();
	auto voxel = voxelizer.getVoxel();

	std::ofstream stream("test2.txt");
	for (int i = 0; i < voxel->getResolutions()[0]; ++i) {
		for (int j = 0; j < voxel->getResolutions()[1]; ++j) {
			for (int k = 0; k < voxel->getResolutions()[2]; ++k) {
				if (voxel->getValue(i, j, k)) {
					auto p = voxel->getCellPosition(i, j, k);
					stream << p.x << " " << p.y << " " << p.z << std::endl;
				}
			}
		}
	}

	auto scene = new VoxelScene(getWorld()->getNextSceneId(), "Voxelized", std::move(voxel));


	auto presenter = scene->getPresenter();
	presenter->createView(getWorld()->getRenderer(), *getWorld()->getGLFactory());

}