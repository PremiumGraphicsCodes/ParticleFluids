#include "MoveButton.h"

#include "imgui.h"
#include "../UI/MoveUICtrl.h"
#include "../UI/CameraUICtrl.h"
#include "../Scene/IShapeScene.h"

using namespace Crystal::Scene;
using namespace Crystal::UI;

void MoveButton::onShow()
{
	objectButton.show();
	if (ImGui::Button("Move")) {
		auto ctrl = new MoveUICtrl(getModel(), getCanvas());
		auto object = getModel()->getObjects()->findSceneById(objectButton.getId());
		if (object == nullptr) {
			return;
		}
		ctrl->add(static_cast<IShapeScene*>(object));
		getCanvas()->setUICtrl(ctrl);
	}
}

void MoveButton::onOk()
{
	auto ctrl = new CameraUICtrl(getCanvas()->getCamera());
	getCanvas()->setUICtrl(ctrl);
}

void MoveButton::onCancel()
{
	auto ctrl = new CameraUICtrl(getCanvas()->getCamera());
	getCanvas()->setUICtrl(ctrl);
}