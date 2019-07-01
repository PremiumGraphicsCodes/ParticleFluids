#include "PMQuadButton.h"

#include "../Shape/PolygonMeshBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::UI;

PMQuadButton::PMQuadButton(Repository* model, Canvas* canvas) :
	IPopupButton("PMQuad", model, canvas),
	quad("Quad"),
	materialId("MaterialId", 1),
	name("Name", "PMPlane")
{
}

void PMQuadButton::onShow()
{
	quad.show();
	materialId.show();
	name.show();
}

void PMQuadButton::onOk()
{
	PolygonMeshBuilder builder;
	builder.add(quad.getValue());
	builder.pushCurrentFaceGroup();
	getModel()->getObjects()->getFactory()->createPolygonMeshScene(builder.getPolygonMesh(), nullptr, name.getValue());
	getCanvas()->setViewModel(getModel()->toViewModel());
	getCanvas()->fitCamera(getModel()->getBoundingBox());
}

void PMQuadButton::onCancel()
{
}
