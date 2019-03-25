#include "PMBoxButton.h"

#include "../Shape/PolygonMeshBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::UI;

void PMBoxButton::onShow()
{
	boxView.show();
	attribute.show();
}

void PMBoxButton::onOk()
{
	PolygonMeshBuilder builder;
	builder.build(boxView.getValue());
	getModel()->getObjects()->getPolygonMeshes()->addObject(builder.getPolygonMesh(), attribute.getValue(), "PMBox");
	getCanvas()->setViewModel(getModel()->toViewModel());
	getCanvas()->fitCamera(getModel()->getBoundingBox());
}
