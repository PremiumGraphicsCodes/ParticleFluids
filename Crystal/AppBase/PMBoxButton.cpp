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
	auto scene = getModel()->getObjects()->getFactory()->createPolygonMeshScene(builder.getPolygonMesh(), nullptr, name.getValue());
	getModel()->getObjects()->addScene(scene);
	getCanvas()->setViewModel(getModel()->toViewModel());
	getCanvas()->fitCamera(getModel()->getBoundingBox());
}
