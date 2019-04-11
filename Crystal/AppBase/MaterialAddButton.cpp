#include "MaterialAddButton.h"

#include "../Graphics/Material.h"

using namespace Crystal::Graphics;
using namespace Crystal::UI;

MaterialAddButton::MaterialAddButton(Repository* model, Canvas* canvas) :
	IPopupButton("Material", model, canvas),
	ambient("Ambient", glm::vec4(0, 0, 0, 0)),
	diffuse("Diffuse", glm::vec4(0, 0, 0, 0)),
	specular("Specular", glm::vec4(0, 0, 0, 0)),
	shininess("Shininess", 1.0f),
	name("Name", "Material1")
{
}

void MaterialAddButton::onShow()
{
	ambient.show();
	diffuse.show();
	specular.show();
	shininess.show();
	name.show();
}

void MaterialAddButton::onOk()
{
	Material* m = new Material();
	m->setAmbient(ambient.getValue());
	m->setDiffuse(diffuse.getValue());
	m->setSpecular(specular.getValue());
	m->setShininess(shininess.getValue());
	getModel()->getAppearances()->getMaterials()->add(m, name.getValue());
	getCanvas()->setViewModel(getModel()->toViewModel());
	getCanvas()->fitCamera(getModel()->getBoundingBox());
}
