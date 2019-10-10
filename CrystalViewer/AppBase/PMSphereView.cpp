#include "PMSphereView.h"

#include "../Scene/PolygonMeshBuilder.h"
#include "../Scene/PolygonMeshScene.h"

#include "../Command/CameraFitCommand.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::UI;
using namespace Crystal::Command;

PMSphereView::PMSphereView(World* model, Canvas* canvas) :
	IOkCancelView("PMSphere", model, canvas),
	sphere("Sphere"),
	unum("UNum", 36),
	vnum("VNum", 36),
	name("Name", "PMSphere")
{
	add(&sphere);
	add(&unum);
	add(&vnum);
	add(&name);
}

void PMSphereView::onOk()
{
	PolygonMeshBuilder builder;
	builder.add(sphere.getValue(), unum.getValue(), vnum.getValue());
	auto scene = getWorld()->getObjectFactory()->createPolygonMeshScene(builder.getPolygonMesh(), name.getValue());
	getWorld()->getObjects()->addScene(scene);
	getWorld()->updateViewModel();

	CameraFitCommand command;
	command.execute(model);
}
