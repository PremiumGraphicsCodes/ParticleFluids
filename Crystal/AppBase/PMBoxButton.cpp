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
	builder.add(boxView.getValue());
	builder.pushCurrentFaceGroup();
	getModel()->getObjects()->getPolygonMeshes()->addPolygonMeshScene(builder.getPolygonMesh(), name.getValue());
	getCanvas()->setViewModel(getModel()->toViewModel());
	getCanvas()->fitCamera(getModel()->getBoundingBox());
}
