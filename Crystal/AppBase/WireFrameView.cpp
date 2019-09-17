#include "WireFrameView.h"

#include "../Scene/WireFrame.h"

using namespace Crystal::Shape;
using namespace Crystal::UI;

WireFrameView::WireFrameView(const std::string& name) :
	IWindow(name),
	edgeCount("Edges")
{}

void WireFrameView::onShow()
{
	edgeCount.show();
}

void WireFrameView::setValue(WireFrame* value)
{
	edgeCount.setValue(value->getLines().size());
}
