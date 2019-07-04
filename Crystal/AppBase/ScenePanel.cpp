#include "ScenePanel.h"

#include "../UI/Repository.h"

#include "imgui.h"

using namespace Crystal::Model;
using namespace Crystal::UI;

ScenePanel::ScenePanel(const std::string& name, Repository* model, Canvas* canvas) :
	IPanel(name, model, canvas)
{
}

void ScenePanel::show()
{
	ImGui::Begin("Scene");
	show(model->getObjects());
	/*
	auto root = model->getObjects()->getName();
	const auto str = root.c_str();
	if (ImGui::TreeNode(str)) {
		const auto& children = model->getObjects()->getChildren();
		for (auto child : children) {
			const auto& name = child->getName();
			const auto str = name.c_str();
			if (ImGui::TreeNode(str)) {
				ImGui::TreePop();
			}
		}
		ImGui::TreePop();
	}
	*/
	ImGui::End();
}

void ScenePanel::show(IScene* scene)
{
	const auto& name = scene->getName();
	const auto str = name.c_str();
	if (ImGui::TreeNode(str)) {
		const auto& children = scene->getChildren();
		for (auto child : children) {
			show(child);
		}
		ImGui::TreePop();
	}
}
