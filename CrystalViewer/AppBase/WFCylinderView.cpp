#include "WFCylinderView.h"

#include "../../Crystal/Math/Cylinder3d.h"
#include "../../Crystal/Shape/WireFrameBuilder.h"
#include "../../Crystal/Scene/WireFrameScene.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;

WFCylinderView::WFCylinderView(const std::string& name, World* world, Canvas* canvas) :
	IWFAddView(name, world, canvas),
	cylinderView("Cylinder"),
	unumView("UNum", 12)
{
	add(&cylinderView);
	add(&unumView);
}

void WFCylinderView::onOk()
{
	WireFrameBuilder builder;
	builder.build(cylinderView.getValue(), unumView.getValue());
	IWFAddView::addWireFrame(builder.getPositions(), builder.getEdges());
}
