#include "ClearCommand.h"

#include "Public/ClearLabels.h"

using namespace Crystal::Scene;
using namespace Crystal::Command;

std::string ClearCommand::getName()
{
	return ClearLabels::CommandNameLabel;
}

ClearCommand::Args::Args() :
	layer(ClearLabels::LayerLabel, 0)
{
	add(&layer);
}

ClearCommand::ClearCommand() :
	ICommand(&args, nullptr)
{}

bool ClearCommand::execute(World* world)
{
	world->clear(args.layer.getValue());
	return true;
}
