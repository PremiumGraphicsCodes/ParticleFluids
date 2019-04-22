#include "PositionSelectButton.h"

#include "imgui.h"
#include "../UI/PickUICtrl.h"

using namespace Crystal::Model;
using namespace Crystal::UI;

void PositionSelectButton::onShow()
{
	ImGui::InputFloat3("Position", &position[0]);
	if (ImGui::Button("Pick")) {
		auto ctrl = new PickUICtrl(getModel(), getCanvas(), ObjectType::PolygonMeshObject);
		auto model = getModel();
		//model->getObjects()->getParticleSystems()->findParticleById();
		auto func = [=](int parentId, int childId) {
			auto particle = model->getObjects()->getParticleSystems()->findParticleById(parentId, childId);
			if (particle != nullptr) {
				this->position = particle->getPosition();
			}
		};
		ctrl->setFunction(func);
		getCanvas()->setUICtrl(ctrl);
	}
}

void PositionSelectButton::onOk()
{
	getCanvas()->setViewModel(getModel()->toViewModel());
	getCanvas()->fitCamera(getModel()->getBoundingBox());
}

void PositionSelectButton::onCancel()
{
}