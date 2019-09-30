#include "CameraMenu.h"
#include "imgui.h"
#include "../Scene/World.h"
#include "Canvas.h"
#include "../Command/CameraFitCommand.h"

using namespace Crystal::Scene;
using namespace Crystal::UI;
using namespace Crystal::Command;

void CameraMenu::onShow()
{
	auto canvas = getCanvas();
	auto model = getModel();

	const auto c = name.c_str();
	if (ImGui::BeginMenu(c)) {
		if (ImGui::MenuItem("Fit")) {
			CameraFitCommand command;
			command.execute(model);
		}
		/*
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
		*/
		ImGui::EndMenu();
	}
	//ImGui::EndMenuBar();

}
