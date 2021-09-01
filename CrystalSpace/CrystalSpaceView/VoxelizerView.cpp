#include "VoxelizerView.h"

#include "../CrystalSpace/Voxelizer.h"
#include "../../Crystal/Scene/VoxelScene.h"

#include "../../Crystal/Scene/ParticleSystemScene.h"
#include "../../Crystal/Scene/PolygonMeshScene.h"

#include "../../Crystal/Shape/PolygonMeshBuilder.h"
#include "../../Crystal/Math/Sphere3d.h"

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

void VoxelizerView::onOk()
{
	PolygonMeshBuilder builder;
	//const Box3d box(Vector3dd(0, 0, 0), Vector3dd(5, 10, 10));
	//builder.add(box, 2, 2, 2);
	const Sphere3dd sphere(Vector3dd(0, 0, 0), 5);
	builder.add(sphere, 32, 32);
	auto mesh = builder.build();

	Voxelizer voxelizer;
	auto voxel = voxelizer.voxelize(*mesh, 1.0);
	auto scene = new VoxelScene(getWorld()->getNextSceneId(), "Voxelized", std::move(voxel));

	auto presenter = scene->getPresenter();
	presenter->createView(getWorld()->getRenderer(), *getWorld()->getGLFactory());

}