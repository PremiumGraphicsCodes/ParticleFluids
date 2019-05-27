#include "MaskMenu.h"
#include "imgui.h"
#include "../UI/Repository.h"
#include "../UI/Canvas.h"

using namespace Crystal::UI;

void MaskMenu::show()
{
	auto model = getModel();
	auto canvas = getCanvas();

	const auto& c = name.c_str();
	if (ImGui::BeginMenu(c)) {
		auto mask = canvas->getMask();
		if (ImGui::MenuItem("Point")) {
			mask.showPoints = !mask.showPoints;
			canvas->setMask(mask);
			canvas->setViewModel(model->toViewModel());
		}
		if (ImGui::MenuItem("Line")) {
			mask.showLines = !mask.showLines;
			canvas->setMask(mask);
			canvas->setViewModel(model->toViewModel());
		}
		if (ImGui::MenuItem("Triangle")) {
			mask.showTrianlges = !mask.showTrianlges;
			canvas->setMask(mask);
			canvas->setViewModel(model->toViewModel());
		}

		ImGui::EndMenu();
	}
}
