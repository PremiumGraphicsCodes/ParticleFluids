#include "BoundaryView.h"

#include "../CrystalPhysics/Boundary.h"
#include "../../Crystal/Scene/PolygonMeshScene.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::UI;
using namespace Crystal::Physics;

BoundaryView::BoundaryView(const std::string& name, World* model, Canvas* canvas) :
	IOkCancelView(name, model, canvas),
	meshSelectView(name, model, canvas),
	divideLengthView("DivideLength", 1.0)
{
	add(&meshSelectView);
	add(&divideLengthView);
}

void BoundaryView::onOk()
{
	auto mesh = getWorld()->getScenes()->findSceneById<PolygonMeshScene*>(meshSelectView.getId());
	if (mesh == nullptr) {
		return;
	}
	boundary.build(*(mesh->getShape()), divideLengthView.getValue());
}
