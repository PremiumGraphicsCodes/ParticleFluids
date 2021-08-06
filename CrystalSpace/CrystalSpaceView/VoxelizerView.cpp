#include "VoxelizerView.h"


#include "../CrystalSpace/Voxelizer.h"
//#include "../CrystalSpace/VoxelScene.h"

#include "../../Crystal/Scene/ParticleSystemScene.h"
#include "../../Crystal/Scene/PolygonMeshScene.h"

#include "../../Crystal/Shape/PolygonMeshBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::Space;
using namespace Crystal::UI;

VoxelizerView::VoxelizerView(const std::string& name, World* model, Canvas* canvas) :
	IOkCancelView(name, model, canvas)
//	divideLengthView("DivideLength", 1.0)
{
//	add(&divideLengthView);
}

void VoxelizerView::onOk()
{
	PolygonMeshBuilder builder;
	const Box3d box(Vector3dd(0, 0, 0), Vector3dd(10, 10, 10));
	builder.add(box, 2, 2, 2);
	auto mesh = builder.build();

	/*
	MeshToVoxelConverter converter;
	converter.convert(*mesh, 1.0);
	auto voxel = converter.toVoxel();
	auto scene = new VoxelScene(getWorld()->getNextSceneId(), "Voxel", std::move(voxel));

	//auto scene = new VoxelScene(getWorld()->getNextSceneId(), nameView.getValue(), std::move(voxel));
	getWorld()->getScenes()->addScene(scene);

	auto presenter = scene->getPresenter();
	presenter->createView(getWorld()->getRenderer(), *getWorld()->getGLFactory());
	*/
}