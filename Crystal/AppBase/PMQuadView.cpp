#include "PMQuadView.h"

#include "../Shape/PolygonMeshBuilder.h"

#include "../Scene/World.h"
#include "../UI/Canvas.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;

PMQuadView::PMQuadView(World* model, Canvas* canvas) :
	IOkCancelView("PMQuad", model, canvas),
	quad("Quad"),
	materialName("Material", ""),
	name("Name", "PMPlane")
{
}

void PMQuadView::show()
{
	quad.show();
	materialName.show();
	name.show();
	IOkCancelView::show();
}

void PMQuadView::onOk()
{
	PolygonMeshBuilder builder;
	builder.add(quad.getValue());
	auto scene = getRepository()->getObjectFactory()->createPolygonMeshScene(builder.getPolygonMesh(), name.getValue());
	scene->setMaterialName(materialName.getValue());
	getRepository()->getObjects()->addScene(scene);
	getRepository()->updateViewModel();
	getCanvas()->fitCamera(getRepository()->getBoundingBox());
}
