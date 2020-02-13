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
using namespace Crystal::Shape;
using namespace Crystal::UI;
using namespace Crystal::Command;

PMQuadView::PMQuadView(const std::string& name, World* world, Canvas* canvas) :
	IOkCancelView(name, world, canvas),
	quadView("Quad"),
	nameView("Name", "PMPlane")
{
	add(&quadView);
	add(&nameView);
}

void PMQuadView::onOk()
{
	PolygonMeshBuilder builder;
	builder.add(quadView.getValue());

	Command::Command command;
	command.create(PolygonMeshCreateLabels::CommandNameLabel);
	command.setArg(PolygonMeshCreateLabels::PositionsLabel, builder.getPositions());
	command.setArg(PolygonMeshCreateLabels::NormalsLabel, builder.getNormals());
	command.setArg(PolygonMeshCreateLabels::TexCoordsLabel, builder.getTexCoords());
	command.setArg(PolygonMeshCreateLabels::VerticesLabel, builder.getVertices());
	command.setArg(PolygonMeshCreateLabels::FacesLabel, builder.getFaces());
	command.setArg(PolygonMeshCreateLabels::NameLabel, nameView.getValue());
	command.execute(getWorld());

	command.create(CameraFitCommandLabels::CameraFitCommandLabel);
	command.execute(getWorld());
	getWorld()->updateViewModel();
}
