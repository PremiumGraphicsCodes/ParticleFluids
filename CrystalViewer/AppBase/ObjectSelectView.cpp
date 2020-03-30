#include "ObjectSelectView.h"

#include "imgui.h"
#include "PickUICtrl.h"
#include "CameraUICtrl.h"

#include "../Command/Public/ShapeSelectLabels.h"
#include "../Command/Command.h"
#include "../../Crystal/Shape/WireFrameBuilder.h"
#include "../../Crystal/Scene/WireFrameScene.h"

using namespace Crystal::Shape;
using namespace Crystal::UI;
using namespace Crystal::Scene;
using namespace Crystal::Command;

ObjectSelectView::ObjectSelectView(const std::string& name, World* model, Canvas* canvas) :
	ObjectSelectView(name, model, canvas, Scene::SceneType::All)
{
}

ObjectSelectView::ObjectSelectView(const std::string& name, World* model, Canvas* canvas, const SceneType type) :
	IView(name),
	idView("Id", 0),
	pickButton("Pick"),
	type(type)
{
	pickButton.setFunction([=] {
		auto ctrl = new PickUICtrl(model, canvas, type);
		auto func = [=](int parentId, int childId) {
			Command::Command command(ShapeSelectLabels::CommandNameLabel);
			command.setArg(ShapeSelectLabels::ShapeIdLabel, parentId);
			if (command.execute(model)) {
				const auto bb = model->getObjects()->findSceneById( parentId )->getBoundingBox();
				WireFrameBuilder builder;
				builder.build(bb);
				WireFrameAttribute attribute;
				attribute.color = glm::vec4(1.0, 0.0, 0.0, 0.0);
				attribute.width = 1.0f;
				auto bbshape = model->getSceneFactory()->createWireFrameScene(builder.createWireFrame(), attribute, "BoundingBox");
				model->getItems()->addScene(bbshape);
//				results.boundingBoxItemId.setValue(bbshape->getId());
			}

			//model->getObjects()->findSceneById(parentId)->setSelected(true);

			//model->updateViewModel();
			return this->idView.setValue(parentId);
		};
		ctrl->setFunction(func);
		canvas->setUICtrl(ctrl);
	});
	add(&idView);
	add(&pickButton);

}

