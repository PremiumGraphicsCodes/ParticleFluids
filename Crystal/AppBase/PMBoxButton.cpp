#include "PMBoxButton.h"

#include "../Shape/PolygonMeshBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::UI;

void PMBoxButton::onShow()
{
	boxView.show();
}

void PMBoxButton::onOk()
{
	PolygonMeshBuilder* builder = getModel()->getObjects()->getPolygonMeshes()->getBuilder();
	builder->build(boxView.getValue());
	Crystal::Graphics::Material material;
	material.setAmbient(glm::vec3(1, 0, 0));
	material.setSpecular(glm::vec3(0, 1, 0));
	material.setDiffuse(glm::vec3(0, 0, 1));
	getModel()->getObjects()->getPolygonMeshes()->addObject(builder->getPolygonMesh(), material, "PMBox");
	getCanvas()->setViewModel(getModel()->toViewModel());
	getCanvas()->fitCamera(getModel()->getBoundingBox());
}
