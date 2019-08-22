#include "WFSphereView.h"

#include "../Math/Sphere3d.h"
#include "../Shape/WireFrameBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;

WFSphereView::WFSphereView(World* repository, Canvas* canvas) :
	IOkCancelView("WFSphere", repository, canvas),
	sphere("Sphere"),
	attribute("Attribute"),
	unum("UNum", 12),
	vnum("VNum", 12)
{
}

void WFSphereView::onShow()
{
	sphere.show();
	unum.show();
	vnum.show();
	attribute.show();
}

void WFSphereView::onOk()
{
	WireFrameBuilder builder;
	builder.build(sphere.getValue(), unum.getValue(), vnum.getValue());
	auto scene = getWorld()->getObjectFactory()->createWireFrameScene(builder.getWireFrame(), attribute.getValue(), "Sphere");
	getWorld()->getObjects()->addScene(scene);
	getWorld()->updateViewModel();
	getCanvas()->fitCamera(getWorld()->getBoundingBox());
}
