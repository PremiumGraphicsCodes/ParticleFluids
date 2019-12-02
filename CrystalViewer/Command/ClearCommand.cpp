#include "ClearCommand.h"

using namespace Crystal::Scene;
using namespace Crystal::Command;

std::string ClearCommand::getName()
{
	return "Clear";
}

ClearCommand::Args::Args() :
	layer("Layer", 0)
{
	add(&layer);
}

void ClearCommand::execute(World* world)
{
	world->clear(args.layer.getValue());
}
