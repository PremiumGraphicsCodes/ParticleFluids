#include "PMQuadView.h"

#include "../Shape/PolygonMeshBuilder.h"

#include "../UI/Repository.h"
#include "../UI/Canvas.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::UI;

PMQuadView::PMQuadView(RootScene* model, Canvas* canvas) :
	IPanel("PMQuad", model, canvas),
	quad("Quad"),
	materialName("Material", ""),
	name("Name", "PMPlane"),
	ok("Ok")
{
	ok.setFunction([=]() {onOk(); });
}

void PMQuadView::show()
{
	quad.show();
	materialName.show();
	name.show();
	ok.show();
}

void PMQuadView::onOk()
{
	PolygonMeshBuilder builder;
	builder.add(quad.getValue());
	auto scene = getRepository()->getObjectFactory()->createPolygonMeshScene(builder.getPolygonMesh(), name.getValue());
	scene->setMaterialName(materialName.getValue());
	getRepository()->getObjects()->addScene(scene);
	getCanvas()->setViewModel(getRepository()->toViewModel());
	getCanvas()->fitCamera(getRepository()->getBoundingBox());
}
