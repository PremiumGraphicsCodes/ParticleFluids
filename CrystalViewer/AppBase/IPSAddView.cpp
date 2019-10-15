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
	command.create(::ParticleSystemAddLabel);
	command.setArg(::PositionsLabel, positions);
	command.setArg(::PointSizeLabel, attributeView.getValue().size);
	command.setArg(::ColorLabel, attributeView.getValue().color);
	command.setArg(::NameLabel, attributeView.getName());
	command.execute(getWorld());

	command.create(::CameraFitCommandLabel);
	command.execute(getWorld());

	//getCanvas()->fitCamera(getWorld()->getBoundingBox());

}