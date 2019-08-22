#include "TransformAddView.h"

#include "../Scene/World.h"
#include "../Scene/TransformScene.h"

#include "Canvas.h"

using namespace Crystal::Scene;
using namespace Crystal::UI;

TransformAddView::TransformAddView(const std::string& name, World* model, Canvas* canvas) :
	IOkCancelView(name, model, canvas),
	transform("Transform", model, canvas)
{
}

void TransformAddView::onShow()
{
	transform.show();
}

void TransformAddView::onOk()
{
	auto scene = getWorld()->getObjectFactory()->createTransformScene("Transform");
	//scene->setTranslate()
	getWorld()->getObjects()->addScene(scene);
	getWorld()->updateViewModel();
	getCanvas()->fitCamera(getWorld()->getBoundingBox());

}