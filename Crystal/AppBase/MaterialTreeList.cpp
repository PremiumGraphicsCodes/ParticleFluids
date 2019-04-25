#include "MaterialTreeList.h"

#include "imgui.h"

using namespace Crystal::UI;


MaterialTreeList::MaterialTreeList(const std::string& name, Repository* model, Canvas* canvas) :
	ITreeList(name, model, canvas),
	editView("Edit",model, canvas)
{
}

void MaterialTreeList::onShow()
{
	const auto& materials = getRepository()->getAppearances()->getMaterials()->getMaterials();

	auto n = getName();
	auto str = n.c_str();

	ImGui::BeginChild("Materials", ImVec2(250, 100), ImGuiWindowFlags_NoTitleBar);
	for (auto l : materials) {
		const auto& str = l->getName();
		auto s = str.c_str();
		if (ImGui::Button(s)) {
			editView.setValue(l);
		}
	}
	//editView.show();
	ImGui::EndChild();
}
