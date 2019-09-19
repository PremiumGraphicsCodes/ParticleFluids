#include "PMBoxView.h"

#include "../Scene/PolygonMeshBuilder.h"
#include "../Scene/PolygonMeshScene.h"
#include "../Scene/World.h"
#include "Canvas.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::UI;

PMBoxView::PMBoxView(World* model, Canvas* canvas) :
	IOkCancelView("PMBox", model, canvas),
	boxView("Box"),
	nameView("Name", "PMBox")
{
	add(&boxView);
	add(&nameView);
}

void PMBoxView::onOk()
{
	PolygonMeshBuilder builder;
	builder.add(boxView.getValue());
	auto scene = getWorld()->getObjectFactory()->createPolygonMeshScene(builder.getPolygonMesh(), nameView.getValue());
	getWorld()->getObjects()->addScene(scene);
	getWorld()->updateViewModel();
	getCanvas()->fitCamera(getWorld()->getBoundingBox());
}
