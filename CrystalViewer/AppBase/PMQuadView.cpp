#include "PMQuadView.h"

#include "../../Crystal/Scene/PolygonMeshBuilder.h"

#include "../../Crystal/Scene/PolygonMeshScene.h"

#include "../../Crystal/Scene/World.h"

#include "../Command/CameraFitCommand.h"

#include "Canvas.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::UI;
using namespace Crystal::Command;

PMQuadView::PMQuadView(World* model, Canvas* canvas) :
	IOkCancelView("PMQuad", model, canvas),
	quad("Quad"),
	name("Name", "PMPlane")
{
	add(&quad);
	add(&name);
}

void PMQuadView::onOk()
{
	PolygonMeshBuilder builder;
	builder.add(quad.getValue(), 1, 1);
	auto scene = getWorld()->getObjectFactory()->createPolygonMeshScene(builder.getPolygonMesh(), name.getValue());
	getWorld()->getObjects()->addScene(scene);
	getWorld()->updateViewModel();
	
	CameraFitCommand command;
	command.execute(model);
}
