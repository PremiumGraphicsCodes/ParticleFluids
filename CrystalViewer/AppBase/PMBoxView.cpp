#include "PMBoxView.h"

#include "../../Crystal/Scene/PolygonMeshBuilder.h"
#include "../../Crystal/Scene/PolygonMeshScene.h"
#include "../../Crystal/Scene/World.h"
#include "Canvas.h"
#include "../Command/CameraFitCommand.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::UI;
using namespace Crystal::Command;

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
	builder.add(boxView.getValue(), 1, 1, 1);
	auto scene = getWorld()->getObjectFactory()->createPolygonMeshScene(builder.getPolygonMesh(), nameView.getValue());
	getWorld()->getObjects()->addScene(scene);
	getWorld()->updateViewModel();

	CameraFitCommand command;
	command.execute(model);
}
