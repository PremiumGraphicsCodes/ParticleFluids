#include "IPSAddView.h"

#include "../Command/Command.h"
#include "../Command/Public/ParticleSystemCreateLabels.h"
#include "../Command/Public/ShaderBuildLabels.h"
#include "../Command/Public/CameraLabels.h"

#include "../../Crystal/Scene/ParticleSystemScene.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::UI;
using namespace Crystal::Command;

IPSAddView::IPSAddView(const std::string& name, World* model, Canvas* canvas) :
	IOkCancelView(name, model, canvas),
	//matrixView("Matrix", Math::Identity()),
	attributeView("PSAttribute"),
	presenterView("Presenter")
{
	//add(&matrixView);
	add(&attributeView);
	add(&presenterView);
}

void IPSAddView::addParticleSystem(const std::vector<Vector3dd>& positions)
{
	Command::Command command;
	command.create(ParticleSystemCreateLabels::ParticleSystemAddLabel);
	command.setArg(ParticleSystemCreateLabels::PositionsLabel, positions);
	command.setArg(ParticleSystemCreateLabels::PointSizeLabel, attributeView.getValue().size);
	command.setArg(ParticleSystemCreateLabels::ColorLabel, attributeView.getValue().color);
	command.setArg(ParticleSystemCreateLabels::NameLabel, attributeView.getName());
//	command.setArg(ParticleSystemCreateLabels::MatrixLabel, matrixView.getValue());
	command.execute(getWorld());
	auto newId = std::any_cast<int>( command.getResult(ParticleSystemCreateLabels::NewIdLabel) );

	command.create(ShaderBuildLabels::CommandNameLabel);
	command.setArg(ShaderBuildLabels::IdLabel, newId);
	command.execute(getWorld());

	command.create(CameraFitCommandLabels::CameraFitCommandLabel);
	command.execute(getWorld());
}