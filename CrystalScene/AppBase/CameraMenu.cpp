#include "CameraMenu.h"
#include "imgui.h"
#include "../Scene/World.h"
#include "Canvas.h"
#include "../Command/Command.h"
#include "../Command/CommandFactory.h"
#include "../Command/CameraFitCommand.h"

using namespace Crystal::Scene;
using namespace Crystal::UI;
using namespace Crystal::Command;

void CameraMenu::onShow()
{
	auto canvas = getCanvas();
	auto model = getWorld();

	const auto c = name.c_str();
	if (ImGui::BeginMenu(c)) {
		if (ImGui::MenuItem("Fit")) {
			CameraFitCommand command;
			command.execute(model);
		}
		if (ImGui::MenuItem("XY")) {
			CameraXYCommand command;
			command.execute(model);
		}
		if (ImGui::MenuItem("YZ")) {
			CameraYZCommand command;
			command.execute(getWorld());
		}
		if (ImGui::MenuItem("ZX")) {
			CameraZXCommand command;
			command.execute(getWorld());
		}
		ImGui::EndMenu();
	}
	//ImGui::EndMenuBar();

}
