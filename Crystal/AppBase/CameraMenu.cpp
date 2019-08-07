#include "CameraMenu.h"
#include "imgui.h"
#include "../Scene/World.h"
#include "../UI/Canvas.h"

using namespace Crystal::Scene;
using namespace Crystal::UI;

void CameraMenu::show()
{
	auto canvas = getCanvas();
	auto model = getModel();

	const auto c = name.c_str();
	if (ImGui::BeginMenu(c)) {
		if (ImGui::MenuItem("Fit")) {
			canvas->fitCamera(model->getBoundingBox());
		}
		if (ImGui::MenuItem("XY")) {
			canvas->setCameraXY(model->getBoundingBox());
		}
		if (ImGui::MenuItem("YZ")) {
			canvas->setCameraYZ(model->getBoundingBox());
		}
		if (ImGui::MenuItem("ZX")) {
			canvas->setCameraZX(model->getBoundingBox());
		}
		if (ImGui::MenuItem("XYZ")) {
//			canvas->set
		}

		ImGui::EndMenu();
	}
	//ImGui::EndMenuBar();

}
