#include "PMSphereView.h"

#include "../../Crystal/Scene/PolygonMeshBuilder.h"
#include "../../Crystal/Scene/PolygonMeshScene.h"

#include "../Command/Command.h"
#include "../Command/Public/CameraLabels.h"

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

	Command::Command cameraFitCommand(CameraFitCommandLabels::CameraFitCommandLabel);
	cameraFitCommand.execute(getWorld());
	getWorld()->updateViewModel();
}
