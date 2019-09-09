#include "PMSphereView.h"

#include "../Shape/PolygonMeshBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;

PMSphereView::PMSphereView(World* model, Canvas* canvas) :
	IOkCancelView("PMSphere", model, canvas),
	sphere("Sphere"),
	unum("UNum", 36),
	vnum("VNum", 36),
	name("Name", "PMSphere")
{
	add(&sphere);
	add(&unum);
	add(&vnum);
	add(&name);
}

void PMSphereView::onOk()
{
	PolygonMeshBuilder builder;
	builder.add(sphere.getValue(), unum.getValue(), vnum.getValue());
	auto scene = getWorld()->getObjectFactory()->createPolygonMeshScene(builder.getPolygonMesh(), name.getValue());
	getWorld()->getObjects()->addScene(scene);
	getWorld()->updateViewModel();
	getCanvas()->fitCamera(getWorld()->getBoundingBox());
}
