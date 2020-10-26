#include "VDBInitCommand.h"

#include "PublicLabels/VDBInitLabels.h"

#include "../VDBConverter/OpenVDBAdapter.h"

using namespace Crystal::OpenVDB;
using namespace Crystal::Scene;

VDBInitCommand::Args::Args()
{
}

VDBInitCommand::Results::Results()
{
}

VDBInitCommand::VDBInitCommand()
{
}

std::string VDBInitCommand::getName()
{
	return ::CommandNameLabel;
}

bool VDBInitCommand::execute(World* world)
{
	OpenVDBAdapter::init();
	return true;
}

