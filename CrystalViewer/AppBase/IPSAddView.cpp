#include "IPSAddView.h"

#include "../Command/Command.h"
#include "../Command/Public/ParticleSystemCreateLabels.h"
#include "../Command/Public/CameraLabels.h"

using namespace Crystal::Math;
using namespace Crystal::UI;
using namespace Crystal::Command;

void IPSAddView::addParticleSystem(const std::vector<Vector3dd>& positions)
{
	Command::Command command;
	command.create(ParticleSystemCreateLabels::ParticleSystemAddLabel);
	command.setArg(ParticleSystemCreateLabels::PositionsLabel, positions);
	command.setArg(ParticleSystemCreateLabels::PointSizeLabel, attributeView.getValue().size);
	command.setArg(ParticleSystemCreateLabels::ColorLabel, attributeView.getValue().color);
	command.setArg(ParticleSystemCreateLabels::NameLabel, attributeView.getName());
	command.execute(getWorld());

	command.create(CameraFitCommandLabels::CameraFitCommandLabel);
	command.execute(getWorld());

	//getCanvas()->fitCamera(getWorld()->getBoundingBox());

}