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
}

void PMSphereButton::onOk()
{
	PolygonMeshBuilder builder;
	builder.build(sphereView.getValue(), unumView.getValue(), vnumView.getValue());
	Crystal::Graphics::Material material;
	material.setAmbient(glm::vec3(1, 0, 0));

	material.setDiffuse(glm::vec3(0, 1, 0));
	getModel()->getObjects()->getPolygonMeshes()->addObject(builder.getPolygonMesh(), material, "Sphere");
	getCanvas()->setViewModel(getModel()->toViewModel());
	getCanvas()->fitCamera(getModel()->getBoundingBox());
}
