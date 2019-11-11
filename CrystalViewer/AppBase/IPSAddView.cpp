#include "IPSAddView.h"

#include "../Command/Command.h"
#include "../Command/Public/ParticleSystemAddLabels.h"
#include "../Command/Public/CameraLabels.h"

using namespace Crystal::Math;
using namespace Crystal::UI;
using namespace Crystal::Command;

void IPSAddView::addParticleSystem(const std::vector<Vector3dd>& positions)
{
	Command::Command command;
	command.create(ParticleSystemAddLabels::ParticleSystemAddLabel);
	command.setArg(ParticleSystemAddLabels::PositionsLabel, positions);
	command.setArg(ParticleSystemAddLabels::PointSizeLabel, attributeView.getValue().size);
	command.setArg(ParticleSystemAddLabels::ColorLabel, attributeView.getValue().color);
	command.setArg(ParticleSystemAddLabels::NameLabel, attributeView.getName());
	command.execute(getWorld());

	command.create(CameraFitCommandLabels::CameraFitCommandLabel);
	command.execute(getWorld());

	//getCanvas()->fitCamera(getWorld()->getBoundingBox());

}