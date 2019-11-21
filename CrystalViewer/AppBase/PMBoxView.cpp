#include "PMBoxView.h"

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
