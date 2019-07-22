#include "ScenePanel.h"

#include "../UI/Repository.h"

#include "PolygonMeshEditView.h"
#include "MaterialEditView.h"
#include "LightEditView.h"

#include "imgui.h"

using namespace Crystal::Scene;
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
	else {
		if (ImGui::Button(str)) {
			switch (type) {
				/*
			case SceneType::PolygonMeshScene :
			{
				auto editView = new PolygonMeshEditView("PolygonMeshEdit", model, canvas);
				//auto lightScene = scene->findSceneById<LightScene*>(id);
				//editView->setValue(lightScene);
				control->clear();
				control->add(editView);
				break;

			}
			*/
			case SceneType::LightScene:
			{
				LightEditView* editView = new LightEditView("LightEdit", model, canvas);
					//auto lightScene = scene->findSceneById<LightScene*>(id);
					//editView->setValue(lightScene);
					control->clear();
					control->add(editView);
					break;
				}
				case SceneType::MaterialScene: {
					MaterialEditView* materialView = new MaterialEditView("MaterialEdit", model, canvas);
					auto materialScene = scene->findSceneById<MaterialScene*>(id);
					materialView->setValue(materialScene);
					control->clear();
					control->add(materialView);
					break;
				}
			}
		}
	}
}
