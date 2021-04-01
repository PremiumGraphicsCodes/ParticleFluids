#include "ToVDBVolumeView.h"

#include "../CrystalVDB/VDBVolumeConverter.h"

#include "../../CrystalSpace/CrystalSpace/SparseVolumeScene.h"

#include <iostream>

using namespace Crystal::Scene;
using namespace Crystal::Space;
using namespace Crystal::UI;
using namespace Crystal::VDB;

ToVDBVolumeView::ToVDBVolumeView(const std::string& name, World* model, Canvas* canvas) :
	IOkCancelView(name, model, canvas),
	sphereView("Sphere"),
	resolutionView("Resolution")
{
	add(&sphereView);
	add(&resolutionView);
}

void ToVDBVolumeView::onOk()
{
	std::array<int, 3> resolution =
	{
		resolutionView.getValue(),
		resolutionView.getValue(),
		resolutionView.getValue()
	};
	auto sv = std::make_unique<SparseVolume>(sphereView.getValue().getBoundingBox(), resolution);
	//auto svScene = std::make_unique<SparseVolumeScene>()

	/*
	VDBVolumeConverter converter;
	converter.toVDB()
	auto mesh = new VDBPolygonMeshScene();
	vToMesh.toMesh(grid, mesh);
	mesh->getPresenter()->createView(getWorld()->getRenderer(), *getWorld()->getGLFactory());
	getWorld()->getScenes()->addScene(mesh);

	//EXPECT_FALSE(mesh->getVerticesf().empty());
	//EXPECT_EQ(216, mesh->getQuads().size());
	std::cout << "quads = " << mesh->getQuadFaces().size() << std::endl;;
	*/
}