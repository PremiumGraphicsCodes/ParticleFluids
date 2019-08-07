#include "TransformAddView.h"

#include "../Scene/RootScene.h"
#include "../UI/Canvas.h"
#include "../Scene/TransformScene.h"

using namespace Crystal::Scene;
using namespace Crystal::UI;

TransformAddView::TransformAddView(const std::string& name, RootScene* model, Canvas* canvas) :
	IOkCancelView(name, model, canvas),
	transform("Transform", model, canvas)
{
}

void TransformAddView::show()
{
	transform.show();
	IOkCancelView::show();
}

void TransformAddView::onOk()
{
	auto scene = getRepository()->getObjectFactory()->createTransformScene("Transform");
	//scene->setTranslate()
	getRepository()->getObjects()->addScene(scene);
	getRepository()->updateViewModel();
	getCanvas()->fitCamera(getRepository()->getBoundingBox());

}