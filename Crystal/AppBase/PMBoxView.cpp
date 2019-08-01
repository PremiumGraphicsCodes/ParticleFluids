#include "PMBoxView.h"

#include "../Shape/PolygonMeshBuilder.h"
#include "../Scene/RootScene.h"
#include "../UI/Canvas.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;

PMBoxView::PMBoxView(RootScene* model, Canvas* canvas) :
	IPanel("PMBox", model, canvas),
	boxView("Box"),
	materialName("MaterialName", ""),
	name("Name", "PMBox"),
	ok("Ok")
{
	ok.setFunction([=]() {onOk(); });
}

void PMBoxView::show()
{
	boxView.show();
	materialName.show();
	name.show();
	ok.show();
}

void PMBoxView::onOk()
{
	PolygonMeshBuilder builder;
	builder.add(boxView.getValue());
	auto scene = getRepository()->getObjectFactory()->createPolygonMeshScene(builder.getPolygonMesh(), name.getValue());
	scene->setMaterialName(materialName.getValue());
	getRepository()->getObjects()->addScene(scene);
	getCanvas()->setViewModel(getRepository()->toViewModel());
	getCanvas()->fitCamera(getRepository()->getBoundingBox());
}
