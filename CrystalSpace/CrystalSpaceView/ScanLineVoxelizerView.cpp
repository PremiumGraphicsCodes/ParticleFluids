#include "ScanLineVoxelizerView.h"

#include "../CrystalSpace/ScanLineVoxelizer.h"
#include "../../Crystal/Scene/VoxelScene.h"

//#include "../../Crystal/Scene/ParticleSystemScene.h"
//#include "../../Crystal/Scene/PolygonMeshScene.h"

#include "../../Crystal/Shape/PolygonMeshBuilder.h"
#include "../../Crystal/Math/Sphere3d.h"

#include "../../Crystal/IO/TXTFileWriter.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Graphics;
using namespace Crystal::IO;
using namespace Crystal::Scene;
using namespace Crystal::Space;
using namespace Crystal::UI;

ScanLineVoxelizerView::ScanLineVoxelizerView(const std::string& name, World* model, Canvas* canvas) :
	IOkCancelView(name, model, canvas),
	divideLengthView("DivideLength", 1.0)
{
	//toPointsButton.setFunction([=]() { toPoints(); });
	//toVoxelButton.setFunction([=]() { toVolume(); });

	//add(&toPointsButton);
	//add(&toVoxelButton);

	add(&divideLengthView);
}

void ScanLineVoxelizerView::onOk()
{
	PolygonMeshBuilder builder;
	const Box3d box(Vector3dd(2, 2, 2), Vector3dd(8, 8, 8));
	builder.add(box, 2, 2, 2);
	//const Sphere3dd sphere(Vector3dd(0, 0, 0), 5);
	//builder.add(sphere, 32, 32);
	auto mesh = builder.build();

	ScanLineVoxelizer voxelizer;
	voxelizer.voxelize(*mesh, 1.0);
	auto voxel = voxelizer.getVoxel();

	/*
	std::vector<Math::Vector3dd> positions;
	for (int i = 0; i < voxel->getResolutions()[0]; ++i) {
		for (int j = 0; j < voxel->getResolutions()[1]; ++j) {
			for (int k = 0; k < voxel->getResolutions()[2]; ++k) {
				if (voxel->getValue(i, j, k)) {
					auto p = voxel->getCellPosition(i, j, k);
					positions.push_back(p);
				}
			}
		}
	}
	//TXTFileWriter writer;
	//writer.write("test2.txt", positions);

	auto scene = new VoxelScene(getWorld()->getNextSceneId(), "Voxelized", std::move(voxel));


	auto presenter = scene->getPresenter();
	presenter->createView(getWorld()->getRenderer(), *getWorld()->getGLFactory());
	*/
}