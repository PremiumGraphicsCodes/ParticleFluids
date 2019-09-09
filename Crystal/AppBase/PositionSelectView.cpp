#include "PositionSelectView.h"

#include "imgui.h"
#include "PickUICtrl.h"
#include "CameraUICtrl.h"

using namespace Crystal::Scene;
using namespace Crystal::UI;

void PositionSelectView::onShow()
{
	ImGui::InputFloat3("Position", &position[0]);
	if (ImGui::Button("Pick")) {
		auto ctrl = new PickUICtrl(getWorld(), getCanvas(), SceneType::PolygonMeshScene);
		auto model = getWorld();
		//model->getObjects()->getParticleSystems()->findParticleById();
		auto func = [=](int parentId, int childId) {
			/*
			auto particle = model->getObjects()->getParticleSystems()->findParticleById(parentId, childId);
			if (particle != nullptr) {
				this->position = particle->getPosition();
			}
			*/
		};
		ctrl->setFunction(func);
		getCanvas()->setUICtrl(ctrl);
	}
}