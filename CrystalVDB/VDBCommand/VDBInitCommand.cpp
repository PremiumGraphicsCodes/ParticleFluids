#include "VDBInitCommand.h"

#include "PublicLabels/VDBInitLabels.h"

#include "../CrystalVDB/VDBAdapter.h"

using namespace Crystal::VDB;
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
	VDBAdapter::init();
	return true;
}

