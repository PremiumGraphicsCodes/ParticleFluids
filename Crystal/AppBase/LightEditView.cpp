#include "LightEditView.h"

using namespace Crystal::UI;

LightEditView::LightEditView(const std::string& name, Repository* repository, Canvas* canvas) :
	IWindow(name),
	id("Id", 0),
	light("Light"),
	name("Name", ""),
	repository(repository),
	canvas(canvas)
{
	close();
}

void LightEditView::show()
{
	if (!isVisible()) {
		return;
	}
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
		close();
	}
	if (ImGui::Button("Cancel")) {
		close();
	}
}
