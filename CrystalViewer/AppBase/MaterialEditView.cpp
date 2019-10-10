#include "MaterialEditView.h"

#include "../Graphics/Material.h"

using namespace Crystal::Graphics;
using namespace Crystal::Scene;
using namespace Crystal::UI;

MaterialEditView::MaterialEditView(const std::string& name, World* model, Canvas* canvas) :
	IWindow(name),
	repository(model),
	canvas(canvas),
	id("Id", 0),
	material("Material"),
	name("Name", "Material1"),
	editButton("Edit")
{
	auto func = [=]()
	{
		auto mat = model->getObjects()->findSceneById<MaterialScene*>(id.getValue());
		mat->setMaterial(material.getValue());
		mat->setName(this->name.getValue());
	};
	editButton.setFunction(func);
}

void MaterialEditView::setValue(MaterialScene* value)
{
	this->id.setValue(value->getId());
	this->name.setValue(value->getName());
	this->material.setValue(value->getMaterial());
}

void MaterialEditView::onShow()
{
	id.show();
	material.show();
	name.show();
	editButton.show();
}