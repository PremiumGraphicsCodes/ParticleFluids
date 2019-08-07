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
	materialName("MaterialName", ""),
	name("Name", "PMSphere")
{
}

void PMSphereView::show()
{
	sphere.show();
	unum.show();
	vnum.show();
	materialName.show();
	name.show();
	IOkCancelView::show();
}

void PMSphereView::onOk()
{
	PolygonMeshBuilder builder;
	builder.add(sphere.getValue(), unum.getValue(), vnum.getValue());
	auto scene = getRepository()->getObjectFactory()->createPolygonMeshScene(builder.getPolygonMesh(), name.getValue());
	getRepository()->getObjects()->addScene(scene);
	getRepository()->updateViewModel();
	getCanvas()->fitCamera(getRepository()->getBoundingBox());
}
