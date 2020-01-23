#include "MaterialEditView.h"

#include "../../Crystal/Graphics/Material.h"
#include "../../Crystal/Scene/MaterialScene.h"

using namespace Crystal::Graphics;
using namespace Crystal::Scene;
using namespace Crystal::UI;

MaterialEditView::MaterialEditView(const std::string& name, World* world, Canvas* canvas) :
	IEditCancelView(name, world, canvas),
	id("Id", 0),
	material("Material"),
	name("Name", "Material1")
{
	add(&id);
	add(&material);
	add(&this->name);
}

void MaterialEditView::setValue(MaterialScene* value)
{
	this->id.setValue(value->getId());
	this->name.setValue(value->getName());
	this->material.setValue(value->getMaterial());
}

void MaterialEditView::onEdit()
{
	auto mat = getWorld()->getObjects()->findSceneById<MaterialScene*>(id.getValue());
	mat->setMaterial(material.getValue());
	mat->setName(this->name.getValue());
}