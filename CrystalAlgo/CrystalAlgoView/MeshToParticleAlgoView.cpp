#include "MeshToParticleAlgoView.h"

#include "../CrystalAlgo/MeshToParticleAlgo.h"

#include "../../Crystal/Scene/ParticleSystemScene.h"
#include "../../Crystal/Scene/PolygonMeshScene.h"

#include "../../CrystalViewer/Command/Command.h"
#include "../../CrystalViewer/Command/Public/ParticleSystemCreateLabels.h"
#include "../../CrystalViewer/Command/Public/CameraLabels.h"
#include "../../CrystalViewer/Command/Public/ShaderBuildLabels.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Algo;
using namespace Crystal::UI;

MeshToParticleAlgoView::MeshToParticleAlgoView(const std::string& name, World* model, Canvas* canvas) :
	IOkCancelView(name, model, canvas),
	polygonMeshSelectView("PolygonMesh", model, canvas),
	divideLengthView("DivideLength", 1.0)
{
	add(&polygonMeshSelectView);
	add(&divideLengthView);
}

void MeshToParticleAlgoView::onOk()
{
	auto id = polygonMeshSelectView.getId();
	auto scene = getWorld()->getObjects()->findSceneById<PolygonMeshScene*>(id);
	auto mesh = scene->getShape();

	MeshToParticleAlgo algo;
	algo.subdivide(*mesh, divideLengthView.getValue());
	const auto& positions = algo.getPositions();

	Command::Command command;
	command.create(ParticleSystemCreateLabels::ParticleSystemAddLabel);
	command.setArg(ParticleSystemCreateLabels::PositionsLabel, positions);
	//command.setArg(ParticleSystemCreateLabels::PointSizeLabel, 1.0f);
	//command.setArg(ParticleSystemCreateLabels::ColorLabel, glm::vec4);
	command.setArg(ParticleSystemCreateLabels::NameLabel, "MeshToParticle");
//	command.setArg(ParticleSystemCreateLabels::MatrixLabel, matrixView.getValue());
	command.execute(getWorld());
	auto newId = std::any_cast<int>(command.getResult(ParticleSystemCreateLabels::NewIdLabel));

	command.create(ShaderBuildLabels::CommandNameLabel);
	command.setArg(ShaderBuildLabels::IdLabel, newId);
	command.execute(getWorld());

	command.create(CameraFitCommandLabels::CameraFitCommandLabel);
	command.execute(getWorld());

}