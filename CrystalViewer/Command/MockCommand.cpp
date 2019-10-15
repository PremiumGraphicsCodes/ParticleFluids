#include "MockCommand.h"

#include "Public/MockLabels.h"

using namespace Crystal::Command;

std::string MockCommand::getName()
{
	return ::MockCommandLabel;
}

void MockCommand::execute(Crystal::Scene::World* world)
{
	results.value.setValue( args.lhs.getValue() + args.rhs.getValue() );
}