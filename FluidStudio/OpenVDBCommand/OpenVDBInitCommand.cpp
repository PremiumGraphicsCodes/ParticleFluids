#include "OpenVDBInitCommand.h"

#include "../OpenVDBConverter/OpenVDBAdapter.h"

using namespace Crystal::OpenVDB;
using namespace Crystal::Scene;

OpenVDBInitCommand::Args::Args()
{
}

OpenVDBInitCommand::Results::Results()
{
}

OpenVDBInitCommand::OpenVDBInitCommand()
{
}

std::string OpenVDBInitCommand::getName()
{
	return "VDBInit";
}

bool OpenVDBInitCommand::execute(World* world)
{
	OpenVDBAdapter::init();
	return true;
}

