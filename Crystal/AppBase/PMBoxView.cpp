#include "PMBoxView.h"

#include "../Shape/PolygonMeshBuilder.h"
#include "../UI/Repository.h"
#include "../UI/Canvas.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::UI;

PMBoxView::PMBoxView(Repository* model, Canvas* canvas) :
	IPanel("PMBox", model, canvas),
	boxView("Box"),
	materialId("MaterialId", 1),
	name("Name", "PMBox"),
	ok("Ok")
{
	ok.setFunction([=]() {onOk(); });
}

void PMBoxView::show()
{
	boxView.show();
	materialId.show();
	name.show();
	ok.show();
}

void PMBoxView::onOk()
{
	PolygonMeshBuilder builder;
	builder.add(boxView.getValue());
	auto scene = getRepository()->getObjectFactory()->createPolygonMeshScene(builder.getPolygonMesh(), name.getValue());
	getRepository()->getObjects()->addScene(scene);
	getCanvas()->setViewModel(getRepository()->toViewModel());
	getCanvas()->fitCamera(getRepository()->getBoundingBox());
}
