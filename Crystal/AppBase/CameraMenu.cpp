#include "CameraMenu.h"
#include "imgui.h"
#include "../Scene/World.h"
#include "Canvas.h"
#include "../Command/Command.h"

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
			Command::Command command;
			command.create("CameraFit");
			command.execute(getModel());
		}
		if (ImGui::MenuItem("XY")) {
			Command::Command command;
			command.create("CameraXY");
			command.execute(getModel());
		}
		if (ImGui::MenuItem("YZ")) {
			Command::Command command;
			command.create("CameraYZ");
			command.execute(getModel());
		}
		if (ImGui::MenuItem("ZX")) {
			Command::Command command;
			command.create("CameraZX");
			command.execute(getModel());
		}
		ImGui::EndMenu();
	}
	//ImGui::EndMenuBar();

}
