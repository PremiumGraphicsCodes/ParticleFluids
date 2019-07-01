#include "FaceGroupSelectButton.h"

#include "imgui.h"
#include "../UI/PickUICtrl.h"
#include "../UI/CameraUICtrl.h"

using namespace Crystal::UI;
using namespace Crystal::Model;

void FaceGroupSelectButton::onShow()
{
	if (ImGui::Button("Pick")) {
		auto ctrl = new PickUICtrl(getModel(), getCanvas(), SceneType::PolygonMeshScene);
		auto func = [=](int parentId, int childId) {
			auto mesh = static_cast<PolygonMeshScene*>( getModel()->getObjects()->findSceneById(parentId) );
			if (mesh == nullptr) {
				return;
			}
			auto f = mesh->getShape()->findFaceById(childId);
			if (f == nullptr) {
				return;
			}
			auto g = mesh->getShape()->findGroupByFace(f);
			group.setValue(g);
		};
		ctrl->setFunction(func);
		getCanvas()->setUICtrl(ctrl);
	}
	group.show();
}

void FaceGroupSelectButton::onOk()
{
	auto ctrl = new CameraUICtrl(getCanvas()->getCamera());
	getCanvas()->setUICtrl(ctrl);
}

void FaceGroupSelectButton::onCancel()
{
	auto ctrl = new CameraUICtrl(getCanvas()->getCamera());
	getCanvas()->setUICtrl(ctrl);
}
