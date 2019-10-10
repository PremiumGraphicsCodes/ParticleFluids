#include "LightEditView.h"

using namespace Crystal::Scene;
using namespace Crystal::UI;

LightEditView::LightEditView(const std::string& name, World* repository, Canvas* canvas) :
	IWindow(name),
	id("Id", 0),
	light("Light"),
	name("Name", ""),
	repository(repository),
	canvas(canvas),
	editButton("Edit")
{
	auto func = [=]()
	{
		auto light = repository->getObjects()->findSceneById<LightScene*>(id.getValue());
		light->setLight(this->light.getValue());
		light->setName(this->name.getValue());
	};
	editButton.setFunction(func);
}

void LightEditView::onShow()
{
	id.show();
	light.show();
	name.show();
	editButton.show();
}

void LightEditView::setValue(LightScene* value)
{
	this->id.setValue(value->getId());
	this->light.setValue(value->getLight());
	this->name.setValue(value->getName());
}

