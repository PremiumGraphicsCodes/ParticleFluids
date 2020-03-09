#include "PMBoxView.h"

#include "../../Crystal/Shape/PolygonMeshBuilder.h"
#include "../../Crystal/Scene/PolygonMeshScene.h"
#include "../../Crystal/Scene/World.h"

#include "../Command/Command.h"
#include "../Command/Public/PolygonMeshCreateLabels.h"
#include "../Command/Public/BuildLabels.h"
#include "../Command/Public/CameraLabels.h"

#include "Canvas.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;
using namespace Crystal::Command;

PMBoxView::PMBoxView(const std::string& name, World* world, Canvas* canvas) :
	IOkCancelView(name, world, canvas),
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

	Command::Command command;
	command.create(PolygonMeshCreateLabels::CommandNameLabel);
	command.setArg(PolygonMeshCreateLabels::PositionsLabel, builder.getPositions());
	command.setArg(PolygonMeshCreateLabels::NormalsLabel, builder.getNormals());
	command.setArg(PolygonMeshCreateLabels::TexCoordsLabel, builder.getTexCoords());
	command.setArg(PolygonMeshCreateLabels::VerticesLabel, builder.getVertices());
	command.setArg(PolygonMeshCreateLabels::FacesLabel, builder.getFaces());
	command.setArg(PolygonMeshCreateLabels::NameLabel, nameView.getValue());
	command.execute(getWorld());
	const auto newId = std::any_cast<int>( command.getResult(PolygonMeshCreateLabels::NewIdLabel) );
	
	command.create(BuildLabels::CommandNameLabel);
	command.setArg(BuildLabels::LayerLabel, 1);
	command.setArg(BuildLabels::IdLabel, newId);
	command.execute(getWorld());


	command.create(CameraFitCommandLabels::CameraFitCommandLabel);
	command.execute(getWorld());
	getWorld()->updateViewModel();
}
