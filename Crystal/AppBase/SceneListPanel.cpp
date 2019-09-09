#include "SceneListPanel.h"

#include "../Scene/World.h"

#include "ParticleSystemEditView.h"
#include "WireFrameEditView.h"
#include "PolygonMeshEditView.h"
#include "MaterialEditView.h"
#include "LightEditView.h"
#include "TextureEditView.h"

#include "imgui.h"

using namespace Crystal::Scene;
using namespace Crystal::UI;

SceneListPanel::SceneListPanel(const std::string& name, World* model, Canvas* canvas, IPanel* control) :
	IPanel(name, model, canvas),
	control(control)
{
}

void SceneListPanel::onShow()
{
	ImGui::Begin("SceneList");
	show(model->getObjects());
	ImGui::End();
}

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
	else {
		auto obj = scene->findSceneById(id);
		if (ImGui::Checkbox(str, &obj->_isVisible)) {
			model->updateViewModel();
			switch (type) {
				case SceneType::ParticleSystemScene:
				{
					auto editView = new ParticleSystemEditView("ParticleSystemEdit", model, canvas);
					auto s = scene->findSceneById<ParticleSystemScene*>(id);
					editView->setValue(s);
					control->clear();
					control->add(editView);
					break;
				}
				case SceneType::WireFrameScene:
				{
					auto editView = new WireFrameEditView("WireFrameEdit", model, canvas);
					auto s = scene->findSceneById<WireFrameScene*>(id);
					editView->setValue(s);
					control->clear();
					control->add(editView);
					break;
				}
				case SceneType::PolygonMeshScene:
				{
					auto editView = new PolygonMeshEditView("PolygonMeshEdit", model, canvas);
					auto s = scene->findSceneById<PolygonMeshScene*>(id);
					editView->setValue(s);
					control->clear();
					control->add(editView);
					break;
				}
				case SceneType::LightScene:
				{
					auto editView = new LightEditView("LightEdit", model, canvas);
					auto lightScene = scene->findSceneById<LightScene*>(id);
					editView->setValue(lightScene);
					control->clear();
					control->add(editView);
					break;
				}
				case SceneType::MaterialScene:
				{
					auto editView = new MaterialEditView("MaterialEdit", model, canvas);
					auto materialScene = scene->findSceneById<MaterialScene*>(id);
					editView->setValue(materialScene);
					control->clear();
					control->add(editView);
					break;
				}
				/*
				case SceneType::TextureScene:
				{
					auto editView = new TextureEditView("TextureEdit", model, canvas);
					auto textureScene = scene->findSceneById<TextureScene*>(id);
					editView->setValue(textureScene);
					control->clear();
					control->add(editView);
					break;
				}
				*/
			}
		}
	}
}
