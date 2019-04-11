#include "PMBoxButton.h"

#include "../Shape/PolygonMeshBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::UI;

void PMBoxButton::onShow()
{
	boxView.show();
	materialId.show();
	name.show();
}

void PMBoxButton::onOk()
{
	PolygonMeshBuilder builder;
	builder.build(boxView.getValue());
	getModel()->getObjects()->getPolygonMeshes()->addObject(builder.getPolygonMesh(), materialId.getValue(), name.getValue());
	getCanvas()->setViewModel(getModel()->toViewModel());
	getCanvas()->fitCamera(getModel()->getBoundingBox());
}
