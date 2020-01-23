#include "LightEditView.h"

using namespace Crystal::Scene;
using namespace Crystal::UI;

LightEditView::LightEditView(const std::string& name, World* world, Canvas* canvas) :
	IEditCancelView(name, world, canvas),
	id("Id", 0),
	light("Light"),
	name("Name", "")
{
	add(&id);
	add(&light);
	add(&this->name);
}

void LightEditView::setValue(LightScene* value)
{
	this->id.setValue(value->getId());
	this->light.position.setValue(value->getLight()->getPosition());
	this->light.ambient.setValue( value->getLight()->getAmbient() );
	this->light.diffuse.setValue( value->getLight()->getDiffuse() );
	this->light.specular.setValue( value->getLight()->getSpecular() );
	this->name.setValue(value->getName());
}

void LightEditView::onEdit()
{
	// Todo.
}
