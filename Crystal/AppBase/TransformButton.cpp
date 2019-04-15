#include "TransformButton.h"

#include "imgui.h"
#include "../UI/MoveUICtrl.h"

using namespace Crystal::UI;

void TransformButton::onShow()
{
	objectButton.show();
	if (ImGui::Button("Move")) {
		auto ctrl = new MoveUICtrl(getModel(), getCanvas());
		getCanvas()->setUICtrl(ctrl);
	}
}

void TransformButton::onOk()
{
	getCanvas()->setViewModel(getModel()->toViewModel());
	getCanvas()->fitCamera(getModel()->getBoundingBox());
}
