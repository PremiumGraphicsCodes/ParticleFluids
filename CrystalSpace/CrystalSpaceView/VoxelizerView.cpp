#include "VoxelizerView.h"

#include "../CrystalSpace/Voxelizer.h"
#include "../../Crystal/Scene/VoxelScene.h"

#include "../../Crystal/Scene/ParticleSystemScene.h"
#include "../../Crystal/Scene/PolygonMeshScene.h"

#include "../../Crystal/Shape/PolygonMeshBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Graphics;
using namespace Crystal::Scene;
using namespace Crystal::Space;
using namespace Crystal::UI;

VoxelizerView::VoxelizerView(const std::string& name, World* model, Canvas* canvas) :
	IOkCancelView(name, model, canvas),
	toPointsButton("ToPoints"),
	toVoxelButton("ToVoxel"),
	divideLengthView("DivideLength", 1.0)
{
	toPointsButton.setFunction([=]() { toPoints(); });
	toVoxelButton.setFunction([=]() { toVolume(); });

	add(&toPointsButton);
	add(&toVoxelButton);

	add(&divideLengthView);
}

void VoxelizerView::toPoints()
{
	PolygonMeshBuilder builder;
	const Box3d box(Vector3dd(0, 0, 0), Vector3dd(10, 10, 10));
	builder.add(box, 2, 2, 2);
	auto mesh = builder.build();

	Voxelizer voxelizer;
	const auto points = voxelizer.voxelizeToPoints(*mesh, divideLengthView.getValue());

	ParticleAttribute attr;
	attr.size = 10.0f;
	attr.color = ColorRGBAf(1.0f, 1.0f, 1.0f, 1.0f);
	auto ps = std::make_unique<ParticleSystem<ParticleAttribute>>(points, attr);

	auto scene = new ParticleSystemScene(getWorld()->getNextSceneId(), "Voxelized", std::move(ps));
	getWorld()->getScenes()->addScene(scene);

	auto presenter = scene->getPresenter();
	presenter->createView(getWorld()->getRenderer(), *getWorld()->getGLFactory());
}

void VoxelizerView::toVolume()
{
	PolygonMeshBuilder builder;
	const Box3d box(Vector3dd(0, 0, 0), Vector3dd(10, 10, 10));
	builder.add(box, 2, 2, 2);
	auto mesh = builder.build();

	Voxelizer voxelizer;
	auto voxel = voxelizer.voxelize(*mesh, 1.0);
	auto scene = new VoxelScene(getWorld()->getNextSceneId(), "Voxelized", std::move(voxel));

	auto presenter = scene->getPresenter();
	presenter->createView(getWorld()->getRenderer(), *getWorld()->getGLFactory());
}

void VoxelizerView::onOk()
{
}