#include "PMSphereButton.h"

#include "../Shape/PolygonMeshBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::UI;

PMSphereView::PMSphereView(Repository* model, Canvas* canvas) :
	IPanel("PMSphere", model, canvas),
	sphere("Sphere"),
	unum("UNum", 36),
	vnum("VNum", 36),
	materialName("MaterialName", ""),
	name("Name", "PMSphere"),
	ok("Ok")
{
	ok.setFunction([=]() {onOk(); });
}


void PMSphereView::show()
{
	sphere.show();
	unum.show();
	vnum.show();
	materialName.show();
	name.show();
	ok.show();
}

void PMSphereView::onOk()
{
	PolygonMeshBuilder builder;
	builder.add(sphere.getValue(), unum.getValue(), vnum.getValue());
	auto scene = getRepository()->getObjectFactory()->createPolygonMeshScene(builder.getPolygonMesh(), name.getValue());
	getRepository()->getObjects()->addScene(scene);
	getCanvas()->setViewModel(getRepository()->toViewModel());
	getCanvas()->fitCamera(getRepository()->getBoundingBox());
}
