#include "ObjectSelectButton.h"

#include "imgui.h"
#include "../UI/PickUICtrl.h"
#include "../UI/CameraUICtrl.h"

using namespace Crystal::UI;
using namespace Crystal::Model;

void ObjectSelectButton::onShow()
{
	ImGui::InputInt("Id", &id);
	if (ImGui::Button("Pick")) {
		auto ctrl = new PickUICtrl(getModel(), getCanvas(), Model::ObjectType::All);
		auto func = [=](int parentId, int childId) {
			return this->id = id;
		};
		ctrl->setFunction(func);
		getCanvas()->setUICtrl(ctrl);
	}
}

void ObjectSelectButton::onOk()
{
	auto ctrl = new CameraUICtrl(getCanvas()->getCamera());
	getCanvas()->setUICtrl(ctrl);
}

void ObjectSelectButton::onCancel()
{
	auto ctrl = new CameraUICtrl(getCanvas()->getCamera());
	getCanvas()->setUICtrl(ctrl);
}
