#include "FaceSelectButton.h"
#include "FaceGroupView.h"

#include "imgui.h"
#include "../UI/PickUICtrl.h"
#include "../UI/CameraUICtrl.h"

using namespace Crystal::UI;
using namespace Crystal::Model;

void FaceSelectButton::onShow()
{
	if (ImGui::Button("Pick")) {
		auto ctrl = new PickUICtrl(getModel(), getCanvas(), SceneType::PolygonMeshObject);
		auto func = [=](int parentId, int childId) {
			auto mesh = getModel()->getObjects()->getPolygonMeshes()->findObjectById(parentId);
			if (mesh == nullptr) {
				return;
			}
			auto f = mesh->getShape()->findFaceById(childId);
			if (f == nullptr) {
				return;
			}
			face.setValue(f);
		};
		ctrl->setFunction(func);
		getCanvas()->setUICtrl(ctrl);
	}
	face.show();
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
