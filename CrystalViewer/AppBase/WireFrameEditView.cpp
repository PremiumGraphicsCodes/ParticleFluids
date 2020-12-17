#include "WireFrameEditView.h"

using namespace Crystal::Scene;
using namespace Crystal::UI;

WireFrameEditView::WireFrameEditView(const std::string& name, World* repository, Canvas* canvas) :
	IWindow(name),
	//wire("WireFrame"),
	id("Id"),
	name("Name")
{
}

void WireFrameEditView::onShow()
{
	//wire.show();
	id.show();
	name.show();
}

void WireFrameEditView::setValue(WireFrameScene* value)
{
	//wire.setValue(value);
	id.setValue(value->getId());
	name.setValue(value->getName());
}