#include "TransformButton.h"

#include "imgui.h"
#include "../UI/ObjectTransformUICtrl.h"

using namespace Crystal::UI;

void TransformButton::onShow()
{
	objectButton.show();
	if (ImGui::Button("Pick")) {
		auto ctrl = new ObjectTransformUICtrl(getModel(), getCanvas());
		getCanvas()->setUICtrl(ctrl);
	}
}

void TransformButton::onOk()
{
	getCanvas()->setViewModel(getModel()->toViewModel());
	getCanvas()->fitCamera(getModel()->getBoundingBox());
}
