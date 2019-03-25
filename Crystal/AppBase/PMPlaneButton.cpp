#include "PMPlaneButton.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::UI;

PMPlaneButton::PMPlaneButton(Repository* model, Canvas* canvas) :
	IPopupButton("PMPlane", model, canvas),
	originView("Origin", Vector3dd(0, 0, 0)),
	uvecView("UVec", Vector3dd(1, 0, 0)),
	vvecView("VVec", Vector3dd(0, 1, 0))
{
}

void PMPlaneButton::onShow()
{
	originView.show();
	uvecView.show();
	vvecView.show();
}

void PMPlaneButton::onOk()
{
	PolygonMeshBuilder* builder = getModel()->getObjects()->getPolygonMeshes()->getBuilder();
	builder->build(originView.getValue(), uvecView.getValue(), vvecView.getValue());
	Crystal::Graphics::Material material;
	material.setAmbient(glm::vec3(1, 0, 0));
	getModel()->getObjects()->getPolygonMeshes()->addObject(builder->getPolygonMesh(), material, "PMPlane");
	getCanvas()->setViewModel(getModel()->toViewModel());
	getCanvas()->fitCamera(getModel()->getBoundingBox());
}
