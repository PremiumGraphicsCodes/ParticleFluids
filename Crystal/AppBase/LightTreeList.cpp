#include "LightTreeList.h"

#include "imgui.h"

using namespace Crystal::UI;

LightTreeList::LightTreeList(const std::string& name, Model* model, Canvas* canvas) :
	ITreeList(name, model, canvas)
{
}

void LightTreeList::onShow()
{
	const auto& lights = getModel()->getLights()->getLights();

	auto n = getName();
	auto str = n.c_str();
	ImGui::Begin(str);

	ImGui::BeginChild(str, ImVec2(250, 100), ImGuiWindowFlags_NoTitleBar);
	for (auto l : lights) {
		auto str = l.getName();
		auto s = str.c_str();
		ImGui::Text(s);
	}
	ImGui::EndChild();

	ImGui::End();
}
