#include "MeshBoundaryView.h"

#include "../CrystalPhysics/MeshBoundaryScene.h"
#include "../../Crystal/Scene/PolygonMeshScene.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::UI;
using namespace Crystal::Physics;

MeshBoundaryView::MeshBoundaryView(const std::string& name, World* model, Canvas* canvas) :
	IOkCancelView(name, model, canvas),
	meshSelectView(name, model, canvas),
	divideLengthView("DivideLength", 1.0)
{
	add(&meshSelectView);
	add(&divideLengthView);
}

void MeshBoundaryView::onOk()
{
	auto world = getWorld();

	auto mesh = getWorld()->getScenes()->findSceneById<PolygonMeshScene*>(meshSelectView.getId());
	if (mesh == nullptr) {
		return;
	}
	auto scene = new MeshBoundaryScene(getWorld()->getNextSceneId(), "MeshBoundary");
	scene->build(mesh->getShape(), divideLengthView.getValue());

	scene->getPresenter()->createView(world->getRenderer(), *world->getGLFactory());
	//boundary.build(*(mesh->getShape()), divideLengthView.getValue());
}
