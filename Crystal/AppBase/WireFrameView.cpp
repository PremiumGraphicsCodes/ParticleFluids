#include "WireFrameView.h"

#include "../Shape/WireFrame.h"

using namespace Crystal::Shape;
using namespace Crystal::UI;

WireFrameView::WireFrameView(const std::string& name) :
	IWindow(name),
	edgeCount("Edges")
{}

void WireFrameView::show()
{
	edgeCount.show();
}

void WireFrameView::setValue(WireFrame* value)
{
	edgeCount.setValue(value->getLines().size());
}
