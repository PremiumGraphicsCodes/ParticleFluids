#include "CtrlMenu.h"
#include "imgui.h"
#include "../UI/Repository.h"
#include "../UI/Canvas.h"
#include "../UI/CameraUICtrl.h"
#include "../UI/PickUICtrl.h"
#include "../UI/RectSelectUICtrl.h"

using namespace Crystal::UI;
using namespace Crystal::Scene;

void CtrlMenu::show()
{
	auto model = getModel();
	auto canvas = getCanvas();

	const auto& c = name.c_str();
	if (ImGui::BeginMenu(c)) {
		if (ImGui::MenuItem("Camera")) {
			canvas->setUICtrl(new CameraUICtrl(canvas->getCamera()));
		}
		if (ImGui::MenuItem("Pick")) {
			canvas->setUICtrl(new PickUICtrl(model, canvas, SceneType::All));
		}
		/*
		if (ImGui::MenuItem("Rect")) {
		}
		*/

		ImGui::EndMenu();
	}
}
