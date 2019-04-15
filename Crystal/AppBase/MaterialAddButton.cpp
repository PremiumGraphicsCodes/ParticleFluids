#include "MaterialAddButton.h"

#include "../Graphics/Material.h"

using namespace Crystal::Graphics;
using namespace Crystal::UI;

MaterialAddButton::MaterialAddButton(Repository* model, Canvas* canvas) :
	IPopupButton("MaterialAdd", model, canvas),
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
	getModel()->getAppearances()->getMaterials()->add(material.getValue().clone(), name.getValue());
	getCanvas()->setViewModel(getModel()->toViewModel());
	getCanvas()->fitCamera(getModel()->getBoundingBox());
}
