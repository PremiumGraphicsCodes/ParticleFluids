#include "CtrlMenu.h"
#include "imgui.h"
#include "../Scene/World.h"
#include "Canvas.h"
#include "CameraUICtrl.h"
#include "PickUICtrl.h"

using namespace Crystal::UI;
using namespace Crystal::Scene;

void CtrlMenu::onShow()
{
	auto model = getModel();
	auto canvas = getCanvas();

	const auto& c = name.c_str();
	if (ImGui::BeginMenu(c)) {
		if (ImGui::MenuItem("Camera")) {
			canvas->setUICtrl(new CameraUICtrl(model));
		}
		if (ImGui::MenuItem("Pick")) {
			canvas->setUICtrl(new PickUICtrl(model, canvas, SceneType::All));
		}

		ImGui::EndMenu();
	}
}
