#include "VolumeToMeshView.h"

#include "../VDBConverter/VDBPolygonMesh.h"
#include "../VDBConverter/VDBVolumeConverter.h"

#include <iostream>

using namespace Crystal::Scene;
using namespace Crystal::UI;
using namespace Crystal::VDB;

VolumeToMeshView::VolumeToMeshView(const std::string& name, World* model, Canvas* canvas) :
	IOkCancelView(name, model, canvas),
	particleSystemSelectView("ParticleSystem", model, canvas),
	radiusView("Radius", 5.0)
{
	add(&particleSystemSelectView);
	add(&radiusView);
}

void VolumeToMeshView::onOk()
{
	VDBVolume grid(1.0f);
	grid.fill(1, 6, -1.0f);

	VDBVolumeConverter vToMesh;
	VDBPolygonMesh* mesh = new VDBPolygonMesh();
	vToMesh.toMesh(grid, mesh);
	mesh->getPresenter()->createView(getWorld()->getRenderer(), *getWorld()->getGLFactory());
	getWorld()->getScenes()->addScene(mesh);

	//EXPECT_FALSE(mesh->getVerticesf().empty());
	//EXPECT_EQ(216, mesh->getQuads().size());
	std::cout << "quads = " << mesh->getQuads().size() << std::endl;;
}