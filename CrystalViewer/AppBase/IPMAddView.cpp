#include "IPMAddView.h"

#include "../Command/Command.h"
#include "../Command/Public/PolygonMeshCreateLabels.h"
#include "../Command/Public/CameraLabels.h"

#include "../../Crystal/Scene/PolygonMeshScene.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;
using namespace Crystal::Command;

IPMAddView::IPMAddView(const std::string& name, World* model, Canvas* canvas) :
	IOkCancelView(name, model, canvas),
	matrixView("Matrix", Math::Identity()),
	nameView("Name", "PolygonMesh01")
//	attributeView("PSAttribute")
{
	add(&matrixView);
	add(&nameView);
}

void IPMAddView::addPolygonMesh(const PolygonMeshBuilder& builder)
{
	Command::Command command;
	command.create(PolygonMeshCreateLabels::CommandNameLabel);
	command.setArg(PolygonMeshCreateLabels::PositionsLabel, builder.getPositions());
	command.setArg(PolygonMeshCreateLabels::NormalsLabel, builder.getNormals());
	command.setArg(PolygonMeshCreateLabels::TexCoordsLabel, builder.getTexCoords());
	command.setArg(PolygonMeshCreateLabels::VerticesLabel, builder.getVertices());
	command.setArg(PolygonMeshCreateLabels::FacesLabel, builder.getFaces());
	command.setArg(PolygonMeshCreateLabels::NameLabel, nameView.getValue());
	command.execute(getWorld());
	const auto newId = std::any_cast<int>(command.getResult(PolygonMeshCreateLabels::NewIdLabel));

	auto scene = getWorld()->getScenes()->findSceneById<PolygonMeshScene*>(newId);
	auto controller = scene->getPresenter();
	controller->createView(getWorld()->getRenderer(), *getWorld()->getGLFactory());
	//getWorld()->getRenderer()->getScene()->screen.addChild(controller.getView());

	command.create(CameraFitCommandLabels::CameraFitCommandLabel);
	command.execute(getWorld());

}