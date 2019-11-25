#include "PMQuadView.h"

#include "../../Crystal/Shape/PolygonMeshBuilder.h"

#include "../../Crystal/Scene/PolygonMeshScene.h"

#include "../../Crystal/Scene/World.h"

#include "../Command/Command.h"
#include "../Command/Public/PolygonMeshCreateLabels.h"
#include "../Command/Public/CameraLabels.h"

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

	Command::Command command;
	command.create(PolygonMeshCreateLabels::CommandNameLabel);
	command.setArg(PolygonMeshCreateLabels::PositionsLabel, builder.getPositions());
	command.setArg(PolygonMeshCreateLabels::NormalsLabel, builder.getNormals());
	command.setArg(PolygonMeshCreateLabels::TexCoordsLabel, builder.getTexCoords());
	command.setArg(PolygonMeshCreateLabels::VerticesLabel, builder.getVertices());
	command.setArg(PolygonMeshCreateLabels::FacesLabel, builder.getFaces());
	command.setArg(PolygonMeshCreateLabels::NameLabel, name.getValue());
	command.execute(getWorld());

	command.create(CameraFitCommandLabels::CameraFitCommandLabel);
	command.execute(getWorld());
	getWorld()->updateViewModel();
}
