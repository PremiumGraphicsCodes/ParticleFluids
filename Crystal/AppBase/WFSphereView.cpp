#include "WFSphereView.h"

#include "../Math/Sphere3d.h"
#include "../Scene/WireFrameBuilder.h"
#include "../Scene/WireFrameScene.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::UI;

WFSphereView::WFSphereView(World* repository, Canvas* canvas) :
	IWFAddView("WFSphere", repository, canvas),
	sphere("Sphere"),
	unum("UNum", 12),
	vnum("VNum", 12)
{
	add(&sphere);
	add(&unum);
	add(&vnum);
}

void WFSphereView::onOk()
{
	WireFrameBuilder builder;
	builder.build(sphere.getValue(), unum.getValue(), vnum.getValue());
	IWFAddView::addWireFrame(builder.getWireFrame());
}
