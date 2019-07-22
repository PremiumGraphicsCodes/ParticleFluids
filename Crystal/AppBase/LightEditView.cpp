#include "LightEditView.h"

using namespace Crystal::Scene;
using namespace Crystal::UI;

LightEditView::LightEditView(const std::string& name, Repository* repository, Canvas* canvas) :
	IWindow(name),
	id("Id", 0),
	light("Light"),
	name("Name", ""),
	repository(repository),
	canvas(canvas)
{
	close();
}

void LightEditView::show()
{
	id.show();
	light.show();
	name.show();
}

void LightEditView::setValue(LightScene* value)
{
	this->id.setValue(value->getId());
	this->light.setValue(value->getLight());
	this->name.setValue(value->getName());
}

