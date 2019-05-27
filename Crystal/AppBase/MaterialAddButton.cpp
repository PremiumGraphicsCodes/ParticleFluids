#include "MaterialAddButton.h"

#include "../Graphics/Material.h"

using namespace Crystal::Graphics;
using namespace Crystal::UI;

MaterialAddButton::MaterialAddButton(const std::string& name, Repository* model, Canvas* canvas) :
	IPopupButton(name, model, canvas),
	material("Material"),
	name("Name", "Material1")
{
}

void MaterialAddButton::onShow()
{
	material.show();
}

void MaterialAddButton::onOk()
{
	getModel()->getAppearances()->getMaterials()->add(new Material(material.getValue()), name.getValue());
	getCanvas()->setViewModel(getModel()->toViewModel());
	getCanvas()->fitCamera(getModel()->getBoundingBox());
}
