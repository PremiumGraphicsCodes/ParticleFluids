#include "SceneListPanel.h"

#include "../../Crystal/Scene/World.h"

#include "ParticleSystemEditView.h"
#include "WireFrameEditView.h"
#include "PolygonMeshEditView.h"
#include "FaceGroupEditView.h"
#include "MaterialEditView.h"
#include "LightEditView.h"
#include "TextureEditView.h"

#include "../../Crystal/Scene/TextureScene.h"

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
	show(getWorld()->getScenes());
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
		bool isVisible = scene->isVisible();
		if (ImGui::Checkbox(str, &isVisible)) {
			obj->setVisible(isVisible);
			obj->getPresenter()->updateView();
			switch (type) {
				case SceneType::ParticleSystemScene:
				{
					auto editView = new ParticleSystemEditView("ParticleSystemEdit", getWorld(), getCanvas());
					auto s = scene->findSceneById<ParticleSystemScene*>(id);
					editView->setValue(s);
					control->clear();
					control->add(editView);
					break;
				}
				case SceneType::WireFrameScene:
				{
					auto editView = new WireFrameEditView("WireFrameEdit", getWorld(), getCanvas());
					auto s = scene->findSceneById<WireFrameScene*>(id);
					editView->setValue(s);
					control->clear();
					control->add(editView);
					break;
				}
				case SceneType::PolygonMeshScene:
				{
					auto editView = new PolygonMeshEditView("PolygonMeshEdit", getWorld(), getCanvas());
					auto s = scene->findSceneById<PolygonMeshScene*>(id);
					editView->setValue(s);
					control->clear();
					control->add(editView);
					break;
				}
				case SceneType::FaceGroupScene:
				{
					auto editView = new FaceGroupEditView("FaceGroupEdit", getWorld(), getCanvas());
					auto s = scene->findSceneById<FaceGroupScene*>(id);
					editView->setValue(s);
					control->clear();
					control->add(editView);
					break;
				}
				case SceneType::LightScene:
				{
					auto editView = new LightEditView("LightEdit", getWorld(), getCanvas());
					auto lightScene = scene->findSceneById<LightScene*>(id);
					editView->setValue(lightScene);
					control->clear();
					control->add(editView);
					break;
				}
				case SceneType::MaterialScene:
				{
					auto editView = new MaterialEditView("MaterialEdit", getWorld(), getCanvas());
					auto materialScene = scene->findSceneById<MaterialScene*>(id);
					editView->setValue(materialScene);
					control->clear();
					control->add(editView);
					break;
				}
				case SceneType::TextureScene:
				{
					auto editView = new TextureEditView("TextureEdit", getWorld(), getCanvas());
					auto textureScene = scene->findSceneById<TextureScene*>(id);
					editView->setValue(textureScene);
					control->clear();
					control->add(editView);
					break;
				}
			}
		}
	}
}
