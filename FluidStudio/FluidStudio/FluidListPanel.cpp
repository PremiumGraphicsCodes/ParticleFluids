#include "FluidListPanel.h"

#include "CrystalScene/Scene/World.h"

#include "CrystalScene/AppBase/imgui.h"

#include "CrystalPhysics/CrystalPhysics/MVP/MVPFluidScene.h"
#include "CrystalPhysics/CrystalPhysics/MVP/MVPFluidEmitterScene.h"
#include "FluidView.h"
#include "EmitterView.h"

using namespace Crystal::Scene;
using namespace Crystal::Physics;
using namespace Crystal::UI;

FluidListPanel::FluidListPanel(const std::string& name, World* model, Canvas* canvas, IPanel* control) :
	IPanel(name, model, canvas),
	control(control)
{
}

void FluidListPanel::onShow()
{
	ImGui::Begin("FluidList");
	show(getWorld()->getScenes());
	ImGui::End();
}

void FluidListPanel::show(IScene* scene)
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
		if (ImGui::Button(str)) {
			if (type == Crystal::Physics::MVPFluidScene::Type) {
				auto f = scene->findSceneById<MVPFluidScene*>(id);
				auto fluidView = new FluidView("Fluid", getWorld(), getCanvas());
				fluidView->setValue(f);
				control->clear();
				control->add(fluidView);
			}
			else if (type == Crystal::Physics::MVPFluidEmitterScene::Type) {
				auto f = scene->findSceneById<MVPFluidEmitterScene*>(id);
				auto fluidView = new EmitterView("Fluid", getWorld(), getCanvas());
				fluidView->setValue(f);
				control->clear();
				control->add(fluidView);
			}
			/*
			else if (type == SceneTypeLabels::PolygonMeshScene) {
				auto editView = new PolygonMeshEditView("PolygonMeshEdit", getWorld(), getCanvas());
				auto s = scene->findSceneById<PolygonMeshScene*>(id);
				editView->setValue(s);
				control->clear();
				control->add(editView);
			}
			else if (type == SceneTypeLabels::LightScene) {
				auto editView = new LightEditView("LightEdit", getWorld(), getCanvas());
				auto lightScene = scene->findSceneById<LightScene*>(id);
				editView->setValue(lightScene);
				control->clear();
				control->add(editView);
			}
			else if (type == SceneTypeLabels::MaterialScene) {
				auto editView = new MaterialEditView("MaterialEdit", getWorld(), getCanvas());
				auto materialScene = scene->findSceneById<MaterialScene*>(id);
				editView->setValue(materialScene);
				control->clear();
				control->add(editView);
			}
			else if (type == SceneTypeLabels::TextureScene) {
				auto editView = new TextureEditView("TextureEdit", getWorld(), getCanvas());
				auto textureScene = scene->findSceneById<TextureScene*>(id);
				editView->setValue(textureScene);
				control->clear();
				control->add(editView);
			}
			*/
		}
	}
}
