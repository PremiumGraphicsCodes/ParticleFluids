#include "PMSphereButton.h"

#include "../Shape/PolygonMeshBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::UI;

void PMSphereButton::onShow()
{
	sphereView.show();
	unumView.show();
	vnumView.show();
	attribute.show();
}

void PMSphereButton::onOk()
{
	PolygonMeshBuilder builder;
	builder.build(sphereView.getValue(), unumView.getValue(), vnumView.getValue());

	getModel()->getObjects()->getPolygonMeshes()->addObject(builder.getPolygonMesh(), attribute.getValue(), "Sphere");
	getCanvas()->setViewModel(getModel()->toViewModel());
	getCanvas()->fitCamera(getModel()->getBoundingBox());
}
