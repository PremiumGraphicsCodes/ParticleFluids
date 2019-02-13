#include "ObjectScaleButton.h"

#include "imgui.h"
#include "../UI/PickUICtrl.h"

using namespace Crystal::UI;

void ObjectScaleButton::onShow()
{
	objectButton.show();
	/*
	ImGui::InputInt("Id", &id);
	if (ImGui::Button("Pick")) {
		auto ctrl = new PickUICtrl(getModel(), getCanvas());
		auto func = [=](int id) {
			return this->id = id;
		};
		ctrl->setFunction(func);
		getCanvas()->setUICtrl(ctrl);
	}
	*/
}

void ObjectScaleButton::onOk()
{
	getCanvas()->setViewModel(getModel()->toViewModel());
	getCanvas()->fitCamera(getModel()->getBoundingBox());
}
