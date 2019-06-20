#include "SphereRegionSelectButton.h"
#include "../UI/PickUICtrl.h"
#include "../UI/CameraUICtrl.h"

#include "../Shape/WireFrameBuilder.h"

using namespace Crystal::Shape;
using namespace Crystal::Model;
using namespace Crystal::UI;

void SphereRegionSelectButton::onShow()
{
	if (ImGui::Button("Pick")) {
		auto ctrl = new PickUICtrl(getModel(), getCanvas(), ObjectType::ParticleSystemObject);
		auto model = getModel();
		auto canvas = getCanvas();

		//model->getObjects()->getParticleSystems()->findParticleById();
		auto func = [=](int parentId, int childId) {
			auto particle = model->getObjects()->getParticleSystems()->findParticleById(parentId, childId);
			if (particle != nullptr) {
				auto s = sphere.getValue();
				s.moveTo(particle->getPosition());
				sphere.setValue(s);

				WireFrameBuilder builder;
				builder.build(s, 36, 36);
				WireFrameAttribute attr;
				attr.color = Graphics::ColorRGBAf(1.0, 0.0, 0.0, 0.0);
				attr.width = 1.0;
				model->getItems()->getWireFrames()->addObject(builder.getWireFrame(), attr, "Region");
				canvas->setViewModel(model->toViewModel());
			}
		};
		ctrl->setFunction(func);
		getCanvas()->setUICtrl(ctrl);
	}

	object.show();
	sphere.show();
}

void SphereRegionSelectButton::onOk()
{
	getModel()->getItems()->clear();
	getCanvas()->setViewModel(getModel()->toViewModel());
	auto ctrl = new CameraUICtrl(getCanvas()->getCamera());
	getCanvas()->setUICtrl(ctrl);
}

void SphereRegionSelectButton::onCancel()
{
	getModel()->getItems()->clear();
	getCanvas()->setViewModel(getModel()->toViewModel());
	auto ctrl = new CameraUICtrl(getCanvas()->getCamera());
	getCanvas()->setUICtrl(ctrl);
}
