#include "RotateButton.h"

#include "imgui.h"
#include "../UI/RotateUICtrl.h"
#include "../UI/CameraUICtrl.h"

using namespace Crystal::UI;

void RotateButton::onShow()
{
	objectButton.show();
	if (ImGui::Button("Rotate")) {
		auto ctrl = new RotateUICtrl(getModel(), getCanvas());
		auto object = getModel()->getObjects()->findSceneById(objectButton.getId());
		if (object == nullptr) {
			return;
		}
		ctrl->add(object);
		getCanvas()->setUICtrl(ctrl);
	}
}

void RotateButton::onOk()
{
	auto ctrl = new CameraUICtrl(getCanvas()->getCamera());
	getCanvas()->setUICtrl(ctrl);
}

void RotateButton::onCancel()
{
	auto ctrl = new CameraUICtrl(getCanvas()->getCamera());
	getCanvas()->setUICtrl(ctrl);
}