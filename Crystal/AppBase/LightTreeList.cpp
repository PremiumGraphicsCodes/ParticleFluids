#include "LightTreeList.h"

#include "imgui.h"

using namespace Crystal::UI;

LightTreeList::LightTreeList(const std::string& name, Repository* model, Canvas* canvas) :
	ITreeList(name, model, canvas),
	edit("Edit", model, canvas)
{
}

void LightTreeList::onShow()
{
	const auto& lights = getRepository()->getAppearances()->getLights()->getLights();

	auto n = getName();
	auto str = n.c_str();
	ImGui::Begin(str);

	ImGui::BeginChild(str, ImVec2(250, 100), ImGuiWindowFlags_NoTitleBar);
	for (auto l : lights) {
		const auto str = l->getName();
		auto s = str.c_str();
		/*
		if (ImGui::Button(s)) {
			edit.setValue()
		}
		*/
	}
	ImGui::EndChild();

	ImGui::End();
}
