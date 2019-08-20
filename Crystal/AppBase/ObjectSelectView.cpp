#include "ObjectSelectView.h"

#include "imgui.h"
#include "PickUICtrl.h"
#include "CameraUICtrl.h"

using namespace Crystal::UI;
using namespace Crystal::Scene;

void ObjectSelectView::show()
{
	ImGui::InputInt("Id", &id);
	if (ImGui::Button("Pick")) {
		auto ctrl = new PickUICtrl(getWorld(), getCanvas(), type);
		auto func = [=](int parentId, int childId) {
			return this->id = parentId;
		};
		ctrl->setFunction(func);
		getCanvas()->setUICtrl(ctrl);
	}
}
