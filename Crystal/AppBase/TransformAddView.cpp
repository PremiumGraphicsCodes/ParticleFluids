#include "TransformAddView.h"

#include "../UI/Repository.h"
#include "../UI/Canvas.h"
#include "../Scene/TransformScene.h"

using namespace Crystal::UI;

TransformAddView::TransformAddView(const std::string& name, Repository* model, Canvas* canvas) :
	IPanel(name, model, canvas),
	transform("Transform", model, canvas),
	ok("Ok")
{
	ok.setFunction([=]() { onOk(); });
}

void TransformAddView::show()
{
	transform.show();
	ok.show();
}

void TransformAddView::onOk()
{
	auto scene = getRepository()->getObjectFactory()->createTransformScene("Transform");
	//scene->setTranslate()
	getRepository()->getObjects()->addScene(scene);
	getCanvas()->setViewModel(getRepository()->toViewModel());
	getCanvas()->fitCamera(getRepository()->getBoundingBox());

}