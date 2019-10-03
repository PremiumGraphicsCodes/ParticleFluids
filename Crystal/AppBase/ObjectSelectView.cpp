#include "ObjectSelectView.h"

#include "imgui.h"
#include "PickUICtrl.h"
#include "CameraUICtrl.h"

using namespace Crystal::UI;
using namespace Crystal::Scene;

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
			model->getObjects()->findSceneById(parentId)->setSelected(true);
			model->updateViewModel();
			return this->idView.setValue(parentId);
		};
		ctrl->setFunction(func);
		canvas->setUICtrl(ctrl);
	});
	add(&idView);
	add(&pickButton);

}

