#include "PMBoxView.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;

PMBoxView::PMBoxView(const std::string& name, World* world, Canvas* canvas) :
	IPMAddView(name, world, canvas),
	boxView("Box"),
	nameView("Name", "PMBox")
{
	add(&boxView);
	add(&nameView);
}

void PMBoxView::onOk()
{
	PolygonMeshBuilder builder;
	builder.add(boxView.getValue());

	IPMAddView::addPolygonMesh(builder);
}
