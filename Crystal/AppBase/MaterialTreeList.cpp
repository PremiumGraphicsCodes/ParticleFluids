#include "MaterialTreeList.h"

#include "imgui.h"

#include "MaterialEditView.h"

using namespace Crystal::UI;


MaterialTreeList::MaterialTreeList(const std::string& name, Repository* model, Canvas* canvas) :
	ITreeList(name, model, canvas)
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
			editView = std::make_unique<MaterialEditView>("Edit", getRepository(), getCanvas());
			editView->setValue(l);
			ImGui::OpenPopup(s);
		}
		if (ImGui::BeginPopup(s)) {
			if (editView) {
				editView->show();
			}
			if (ImGui::Button("OK")) {
				ImGui::CloseCurrentPopup();
			}
			if (ImGui::Button("Cancel")) {
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}
	}
	ImGui::EndChild();
}