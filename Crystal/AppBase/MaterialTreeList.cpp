#include "MaterialTreeList.h"

#include "imgui.h"

using namespace Crystal::UI;

MaterialTreeList::MaterialTreeList(const std::string& name, Repository* model, Canvas* canvas) :
	ITreeList(name, model, canvas)
{
}

void MaterialTreeList::onShow()
{
	const auto& materials = getModel()->getAppearances()->getMaterials()->getMaterials();

	auto n = getName();
	auto str = n.c_str();
	ImGui::Begin(str);

	ImGui::BeginChild("Materials", ImVec2(250, 100), ImGuiWindowFlags_NoTitleBar);
	for (auto l : materials) {
		auto str = l.getName();
		auto s = str.c_str();
		ImGui::Text(s);
	}
	ImGui::EndChild();

	ImGui::End();
}
