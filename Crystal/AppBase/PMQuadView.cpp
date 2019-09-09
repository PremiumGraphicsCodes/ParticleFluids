#include "PMQuadView.h"

#include "../Shape/PolygonMeshBuilder.h"

#include "../Scene/World.h"
#include "Canvas.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;

PMQuadView::PMQuadView(World* model, Canvas* canvas) :
	IOkCancelView("PMQuad", model, canvas),
	quad("Quad"),
	name("Name", "PMPlane")
{
	add(&quad);
	add(&name);
}

void PMQuadView::onOk()
{
	PolygonMeshBuilder builder;
	builder.add(quad.getValue());
	auto scene = getWorld()->getObjectFactory()->createPolygonMeshScene(builder.getPolygonMesh(), name.getValue());
	getWorld()->getObjects()->addScene(scene);
	getWorld()->updateViewModel();
	getCanvas()->fitCamera(getWorld()->getBoundingBox());
}
