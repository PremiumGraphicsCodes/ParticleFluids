#include "PositionSelectButton.h"

#include "imgui.h"
#include "../UI/PickUICtrl.h"

using namespace Crystal::UI;

void PositionSelectButton::onShow()
{
	ImGui::InputFloat3("Position", &position[0]);
	if (ImGui::Button("Pick")) {
		auto ctrl = new PickUICtrl(getModel(), getCanvas());
		/*
		auto func = [=](int id) {
			return this->position =
		};
		ctrl->setFunction(func);
		*/
		getCanvas()->setUICtrl(ctrl);
	}
}

void PositionSelectButton::onOk()
{
	getCanvas()->setViewModel(getModel()->toViewModel());
	getCanvas()->fitCamera(getModel()->getBoundingBox());
}
