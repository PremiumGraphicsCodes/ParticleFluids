#include "CameraMenu.h"
#include "imgui.h"
#include "../Scene/World.h"
#include "Canvas.h"
#include "../Command/Command.h"
#include "../Command/CommandFactory.h"
#include "../Command/Public/CameraLabels.h"

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
			auto command = CommandFactory::create(CameraFitCommandLabels::CameraFitCommandLabel);
			command->execute(getWorld());
		}
		if (ImGui::MenuItem("XY")) {
			auto command = CommandFactory::create(CameraFitCommandLabels::CameraXYCommandLabel);
			command->execute(getWorld());
		}
		if (ImGui::MenuItem("YZ")) {
			auto command = CommandFactory::create(CameraFitCommandLabels::CameraYZCommandLabel);
			command->execute(getWorld());
		}
		if (ImGui::MenuItem("ZX")) {
			auto command = CommandFactory::create(CameraFitCommandLabels::CameraZXCommandLabel);
			command->execute(getWorld());
		}
		ImGui::EndMenu();
	}
	//ImGui::EndMenuBar();

}
