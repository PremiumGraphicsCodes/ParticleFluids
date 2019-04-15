#include "ScaleButton.h"

#include "imgui.h"
#include "../UI/ScaleUICtrl.h"

using namespace Crystal::UI;

void ScaleButton::onShow()
{
	objectButton.show();
	if (ImGui::Button("Scale")) {
		auto ctrl = new ScaleUICtrl(getModel(), getCanvas());
		//		getModel()->getObjects()->
		//		ctrl->add(obje)
		getCanvas()->setUICtrl(ctrl);
	}
}

void ScaleButton::onOk()
{
	getCanvas()->setViewModel(getModel()->toViewModel());
	getCanvas()->fitCamera(getModel()->getBoundingBox());
}
