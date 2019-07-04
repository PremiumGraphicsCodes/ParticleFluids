#include "ScenePanel.h"

#include "../UI/Repository.h"

#include "MaterialEditView.h"
#include "LightEditView.h"

#include "imgui.h"

using namespace Crystal::Model;
using namespace Crystal::UI;

ScenePanel::ScenePanel(const std::string& name, Repository* model, Canvas* canvas, IPanel* control) :
	IPanel(name, model, canvas),
	control(control)
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

	if (!scene->isLeaf()) {
		if (ImGui::TreeNode(str)) {
			const auto& children = scene->getChildren();
			for (auto child : children) {
				show(child);
			}
			ImGui::TreePop();
		}
	}
	else {
		if (ImGui::Button(str)) {
			switch (type) {
				case SceneType::LightScene: {
					LightEditView* editView = new LightEditView("LightEdit", model, canvas);
					control->add(editView);
					break;
				}
				case SceneType::MaterialScene: {
					MaterialEditView* materialView = new MaterialEditView("MaterialEdit", model, canvas);
					control->add(materialView);
					break;
				}
			}
		}
	}
}
