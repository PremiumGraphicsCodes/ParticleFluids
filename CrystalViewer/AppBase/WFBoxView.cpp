#include "WFBoxView.h"

#include "../../Crystal/Shape/WireFrameBuilder.h"
#include "../../Crystal/Scene/World.h"
#include "../../Crystal/Scene/WireFrameScene.h"
#include "Canvas.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::UI;

WFBoxView::WFBoxView(World* model, Canvas* canvas) :
	IWFAddView("WFBox", model, canvas),
	box("Box")
{
	add(&box);
}

void WFBoxView::onOk()
{
	WireFrameBuilder builder;
	builder.build(box.getValue());
	IWFAddView::addWireFrame(builder.getPositions(), builder.getEdges());
}