#include "ScenePanel.h"

#include "../UI/Repository.h"

#include "LightEditView.h"

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
	ImGui::End();
}

void ScenePanel::show(IScene* scene)
{
	const auto type = scene->getType();

	const auto& name = scene->getName();
	const auto str = name.c_str();
	if (ImGui::TreeNode(str)) {
		if (type == SceneType::LightScene) {
			LightEditView lightEditView("LightEdit", model, canvas);
			lightEditView.show();
		}

		const auto& children = scene->getChildren();
		for (auto child : children) {
			show(child);
		}
		ImGui::TreePop();
	}
}
