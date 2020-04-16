#include "ShaderSceneListPanel.h"

#include "../../Crystal/Scene/SceneShaderScene.h"

#include "imgui.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::UI;

ShaderSceneListPanel::ShaderSceneListPanel(const std::string& name, World* model, Canvas* canvas, IPanel* control) :
	IPanel(name, model, canvas),
	control(control)
{
}

void ShaderSceneListPanel::onShow()
{
	ImGui::Begin("SceneList");
	//show(model->getShaderScene());
	ImGui::End();
}

/*
void SceneListPanel::show(IScene* scene)
{
	const auto type = scene->getType();

	const auto& name = scene->getName();
	const auto str = name.c_str();
	const auto id = scene->getId();

	if (!scene->isLeaf()) {
		if (ImGui::TreeNode(str)) {
			const auto& children = scene->getChildren();
			for (auto child : children) {
				show(child);
			}
			ImGui::TreePop();
		}
	}
}
*/