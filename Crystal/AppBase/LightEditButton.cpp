#include "LightEditButton.h"

using namespace Crystal::UI;

LightEditButton::LightEditButton(const std::string& name, Repository* repository, Canvas* canvas) :
	IWindow(name),
	id("Id", 0),
	light("Light"),
	name("Name", ""),
	repository(repository),
	canvas(canvas)
{
}

void LightEditButton::show()
{
	id.show();
	light.show();
	name.show();
	if (ImGui::Button("Edit")) {
		auto object = repository->getAppearances()->getLights()->findObjectById(id.getValue());
		if (object == nullptr) {
			return;
		}
		auto light = object->getLight();
		object->setName(name.getValue());
		(*light) = this->light.getValue();
		canvas->setViewModel(repository->toViewModel());
	}
}
