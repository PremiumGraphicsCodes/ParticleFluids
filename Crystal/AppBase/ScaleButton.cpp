#include "ScaleButton.h"

#include "imgui.h"
#include "../UI/ScaleUICtrl.h"

using namespace Crystal::UI;

void ScaleButton::onShow()
{
	objectButton.show();
	if (ImGui::Button("Scale")) {
		auto ctrl = new ScaleUICtrl(getModel(), getCanvas());
		auto object = getModel()->getObjects()->findObjectById(objectButton.getId());
		if (object == nullptr) {
			return;
		}
		ctrl->add(object);
		getCanvas()->setUICtrl(ctrl);
	}
}

void ScaleButton::onOk()
{
	getCanvas()->setViewModel(getModel()->toViewModel());
	getCanvas()->fitCamera(getModel()->getBoundingBox());
}
