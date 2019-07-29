#include "SphereRegionSelectButton.h"
#include "../UI/PickUICtrl.h"
#include "../UI/CameraUICtrl.h"

#include "../Shape/WireFrameBuilder.h"
#include "imgui.h"

using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;

void SphereRegionSelectButton::onShow()
{
	if (ImGui::Button("Pick")) {
		auto mask = (int)SceneType::ParticleSystemScene | (int)SceneType::WireFrameScene | (int)SceneType::PolygonMeshScene;
		auto ctrl = new PickUICtrl(getModel(), getCanvas(), SceneType(mask));
		auto model = getModel();
		auto canvas = getCanvas();

		auto func = [=](int parentId, int childId) {
			auto scene = model->getObjects()->findSceneById<IShapeScene*>(parentId);
			const auto& position = scene->getPosition(childId);
			auto s = sphere.getValue();
			s.moveTo(position);
			sphere.setValue(s);

			WireFrameBuilder builder;
			builder.build(s, 36, 36);
			WireFrameAttribute attr;
			attr.color = Graphics::ColorRGBAf(1.0, 0.0, 0.0, 0.0);
			attr.width = 1.0;
			//model->getItems()->addScene(builder.getWireFrame(), attr, "Region");
			canvas->setViewModel(model->toViewModel());
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
