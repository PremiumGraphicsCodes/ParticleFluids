#include "ObjectMoveButton.h"

#include "imgui.h"
#include "../UI/ObjectMoveUICtrl.h"

using namespace Crystal::UI;

void ObjectMoveButton::onShow()
{
	objectButton.show();
	if (ImGui::Button("Pick")) {
		auto ctrl = new ObjectMoveUICtrl(getModel()->getObjects());
		getCanvas()->setUICtrl(ctrl);
	}
}

void ObjectMoveButton::onOk()
{
	getCanvas()->setViewModel(getModel()->toViewModel());
	getCanvas()->fitCamera(getModel()->getBoundingBox());
}
