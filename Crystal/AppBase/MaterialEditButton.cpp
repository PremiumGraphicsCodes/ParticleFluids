#include "MaterialEditButton.h"

#include "../Graphics/Material.h"

using namespace Crystal::Graphics;
using namespace Crystal::UI;

MaterialEditButton::MaterialEditButton(Repository* model, Canvas* canvas) :
	IPopupButton("MaterialEdit", model, canvas),
	id("Id", 0),
	material("Material"),
	name("Name", "Material1")
{
}

void MaterialEditButton::onShow()
{
	id.show();
	material.show();
	name.show();
}

void MaterialEditButton::onOk()
{
	auto obj = getModel()->getAppearances()->getMaterials()->findObjectById(id.getValue());
	if (obj == nullptr) {
		return;
	}
	auto mat = obj->getMaterial();
	*mat = material.getValue();
	obj->setName(name.getValue());
	getCanvas()->setViewModel(getModel()->toViewModel());
}
