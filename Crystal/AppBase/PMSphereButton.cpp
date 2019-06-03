#include "PMSphereButton.h"

#include "../Shape/PolygonMeshBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::UI;

void PMSphereButton::onShow()
{
	sphere.show();
	unum.show();
	vnum.show();
	materialId.show();
	name.show();
}

void PMSphereButton::onOk()
{
	PolygonMeshBuilder builder;
	//builder.pushCurrentFaceGroup();
	builder.add(sphere.getValue(), unum.getValue(), vnum.getValue());
	builder.build();
	getModel()->getObjects()->getPolygonMeshes()->addObject(builder.getPolygonMesh(), materialId.getValue(), name.getValue());
	getCanvas()->setViewModel(getModel()->toViewModel());
	getCanvas()->fitCamera(getModel()->getBoundingBox());
}
