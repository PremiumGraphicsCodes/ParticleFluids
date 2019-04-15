#include "MoveButton.h"

#include "imgui.h"
#include "../UI/MoveUICtrl.h"

using namespace Crystal::UI;

void MoveButton::onShow()
{
	objectButton.show();
	if (ImGui::Button("Move")) {
		auto ctrl = new MoveUICtrl(getModel(), getCanvas());
//		getModel()->getObjects()->
//		ctrl->add(obje)
		getCanvas()->setUICtrl(ctrl);
	}
}

void MoveButton::onOk()
{
	getCanvas()->setViewModel(getModel()->toViewModel());
	getCanvas()->fitCamera(getModel()->getBoundingBox());
}
