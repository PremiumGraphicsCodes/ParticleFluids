#include "IPSAddView.h"

#include "../Command/Command.h"

using namespace Crystal::Math;
using namespace Crystal::UI;
using namespace Crystal::Command;

void IPSAddView::addParticleSystem(const std::vector<Vector3dd>& positions)
{
	Command::Command command;
	command.create("ParticleSystemAdd");
	command.setArg("Positions", positions);
	command.setArg("PointSize", attributeView.getValue().size);
	command.setArg("Color", attributeView.getValue().color);
	command.setArg("Name", attributeView.getName());
	command.execute(getWorld());

	command.create("CameraFit");
	command.execute(getWorld());

	//getCanvas()->fitCamera(getWorld()->getBoundingBox());

}