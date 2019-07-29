#include "WFSphereView.h"

#include "imgui.h"

#include "../Math/Sphere3d.h"
#include "../Shape/WireFrameBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::UI;

void WFSphereView::show()
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
	auto scene = getRepository()->getObjectFactory()->createWireFrameScene(builder.getWireFrame(), attribute.getValue(), "Sphere");
	getRepository()->getObjects()->addScene(scene);
	getCanvas()->setViewModel(getRepository()->toViewModel());
	getCanvas()->fitCamera(getRepository()->getBoundingBox());
}
