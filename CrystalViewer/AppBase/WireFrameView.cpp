#include "WireFrameView.h"

#include "../../Crystal/Scene/WireFrameScene.h"

using namespace Crystal::Scene;
using namespace Crystal::UI;

WireFrameView::WireFrameView(const std::string& name) :
	IWindow(name),
	edgeCount("Edges")
{}

void WireFrameView::onShow()
{
	edgeCount.show();
}

void WireFrameView::setValue(WireFrameScene* value)
{
	edgeCount.setValue(value->getLines().size());
}
