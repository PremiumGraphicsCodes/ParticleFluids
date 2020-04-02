#include "PMQuadView.h"

#include "../../Crystal/Shape/PolygonMeshBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Shape;
using namespace Crystal::UI;

PMQuadView::PMQuadView(const std::string& name, World* world, Canvas* canvas) :
	IPMAddView(name, world, canvas),
	quadView("Quad"),
	nameView("Name", "PMPlane")
{
	add(&quadView);
	add(&nameView);
}

void PMQuadView::onOk()
{
	PolygonMeshBuilder builder;
	builder.add(quadView.getValue());

	IPMAddView::addPolygonMesh(builder);
}
