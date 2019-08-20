#include "PMBoxView.h"

#include "../Shape/PolygonMeshBuilder.h"
#include "../Scene/World.h"
#include "Canvas.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;

PMBoxView::PMBoxView(World* model, Canvas* canvas) :
	IOkCancelView("PMBox", model, canvas),
	boxView("Box"),
	materialName("MaterialName", ""),
	name("Name", "PMBox")
{
}

void PMBoxView::show()
{
	boxView.show();
	materialName.show();
	name.show();
	IOkCancelView::show();
}

void PMBoxView::onOk()
{
	PolygonMeshBuilder builder;
	builder.add(boxView.getValue());
	auto scene = getWorld()->getObjectFactory()->createPolygonMeshScene(builder.getPolygonMesh(), name.getValue());
	scene->setMaterialName(materialName.getValue());
	getWorld()->getObjects()->addScene(scene);
	getWorld()->updateViewModel();
	getCanvas()->fitCamera(getWorld()->getBoundingBox());
}
