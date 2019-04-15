#include "MaterialTreeList.h"

#include "imgui.h"

using namespace Crystal::UI;


MaterialTreeList::MaterialTreeList(const std::string& name, Repository* model, Canvas* canvas) :
	ITreeList(name, model, canvas),
	editButton(model, canvas)
{
}

void MaterialTreeList::onShow()
{
	const auto& materials = getRepository()->getAppearances()->getMaterials()->getMaterials();

	auto n = getName();
	auto str = n.c_str();
	ImGui::Begin(str);

	ImGui::BeginChild("Materials", ImVec2(250, 100), ImGuiWindowFlags_NoTitleBar);
	for (auto l : materials) {
		const auto& str = l->getName();
		auto s = str.c_str();
		editButton.show();
	}
	ImGui::EndChild();

	ImGui::End();
}
