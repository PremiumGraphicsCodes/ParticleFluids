#include "BoundaryView.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::UI;

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
	auto mesh = model->getObjects()->findSceneById<PolygonMeshScene*>(meshSelectView.getId());
	if (mesh == nullptr) {
		return;
	}
}
