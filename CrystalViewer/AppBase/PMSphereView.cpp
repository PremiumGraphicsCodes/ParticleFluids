#include "PMSphereView.h"

#include "../../Crystal/Shape/PolygonMeshBuilder.h"
#include "../../Crystal/Scene/PolygonMeshScene.h"

#include "../Command/Command.h"
#include "../Command/Public/PolygonMeshCreateLabels.h"
#include "../Command/Public/CameraLabels.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;
using namespace Crystal::Command;

PMSphereView::PMSphereView(const std::string& name, World* world, Canvas* canvas) :
	IOkCancelView(name, world, canvas),
	sphereView("Sphere"),
	unumView("UNum", 36),
	vnumView("VNum", 36),
	nameView("Name", "PMSphere")
{
	add(&sphereView);
	add(&unumView);
	add(&vnumView);
	add(&nameView);
}

void PMSphereView::onOk()
{
	PolygonMeshBuilder builder;
	builder.add( sphereView.getValue(), unumView.getValue(), vnumView.getValue() );

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
