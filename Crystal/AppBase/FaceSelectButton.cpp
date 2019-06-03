#include "FaceSelectButton.h"

#include "imgui.h"
#include "../UI/PickUICtrl.h"
#include "../UI/CameraUICtrl.h"

using namespace Crystal::UI;
using namespace Crystal::Model;

void FaceSelectButton::onShow()
{
	ImGui::InputInt("Id", &id);
	if (ImGui::Button("Pick")) {
		auto ctrl = new PickUICtrl(getModel(), getCanvas(), type);
		auto func = [=](int parentId, int childId) {
			return this->id = parentId;
		};
		ctrl->setFunction(func);
		getCanvas()->setUICtrl(ctrl);
	}
}

void FaceSelectButton::onOk()
{
	auto ctrl = new CameraUICtrl(getCanvas()->getCamera());
	getCanvas()->setUICtrl(ctrl);
}

void FaceSelectButton::onCancel()
{
	auto ctrl = new CameraUICtrl(getCanvas()->getCamera());
	getCanvas()->setUICtrl(ctrl);
}
