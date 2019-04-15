#include "MaterialEditView.h"

#include "../Graphics/Material.h"

using namespace Crystal::Graphics;
using namespace Crystal::UI;

MaterialEditView::MaterialEditView(const std::string& name, Repository* model, Canvas* canvas) :
	IWindow(name),
	repository(model),
	canvas(canvas),
	id("Id", 0),
	material("Material"),
	name("Name", "Material1")
{
}

void MaterialEditView::show()
{
	id.show();
	material.show();
	name.show();

	if (ImGui::Button("Edit")) {
		auto obj = repository->getAppearances()->getMaterials()->findObjectById(id.getValue());
		if (obj == nullptr) {
			return;
		}
		auto mat = obj->getMaterial();
		*mat = material.getValue();
		obj->setName(name.getValue());
		canvas->setViewModel(repository->toViewModel());
	}
}

/*
void MaterialEditButton::onOk()
{
}
*/