#include "ObjectSelectView.h"

#include "imgui.h"
#include "../UI/PickUICtrl.h"
#include "../UI/CameraUICtrl.h"

using namespace Crystal::UI;
using namespace Crystal::Scene;

void ObjectSelectView::show()
{
	ImGui::InputInt("Id", &id);
	if (ImGui::Button("Pick")) {
		auto ctrl = new PickUICtrl(getRepository(), getCanvas(), type);
		auto func = [=](int parentId, int childId) {
			return this->id = parentId;
		};
		ctrl->setFunction(func);
		getCanvas()->setUICtrl(ctrl);
	}
}
