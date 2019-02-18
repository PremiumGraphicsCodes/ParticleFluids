#include "ObjectSelectButton.h"

#include "imgui.h"
#include "../UI/PickUICtrl.h"

using namespace Crystal::UI;

void ObjectSelectButton::onShow()
{
	ImGui::InputInt("Id", &id);
	if (ImGui::Button("Pick")) {
		auto ctrl = new PickUICtrl(getModel(), getCanvas());
		auto func = [=](int parentId, int childId) {
			return this->id = id;
		};
		ctrl->setFunction(func);
		getCanvas()->setUICtrl(ctrl);
	}
}

void ObjectSelectButton::onOk()
{
	getCanvas()->setViewModel(getModel()->toViewModel());
	getCanvas()->fitCamera(getModel()->getBoundingBox());
}
