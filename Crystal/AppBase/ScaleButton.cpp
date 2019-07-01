#include "ScaleButton.h"

#include "imgui.h"
#include "../Scene/IShapeScene.h"
#include "../UI/ScaleUICtrl.h"
#include "../UI/CameraUICtrl.h"

using namespace Crystal::UI;

void ScaleButton::onShow()
{
	objectButton.show();
	if (ImGui::Button("Scale")) {
		auto ctrl = new ScaleUICtrl(getModel(), getCanvas());
		auto object = static_cast<Crystal::Model::IShapeScene*>(getModel()->getObjects()->findSceneById(objectButton.getId()) );
		if (object == nullptr) {
			return;
		}
		ctrl->add(object);
		getCanvas()->setUICtrl(ctrl);
	}
}

void ScaleButton::onOk()
{
	auto ctrl = new CameraUICtrl(getCanvas()->getCamera());
	getCanvas()->setUICtrl(ctrl);
}

void ScaleButton::onCancel()
{
	auto ctrl = new CameraUICtrl(getCanvas()->getCamera());
	getCanvas()->setUICtrl(ctrl);
}