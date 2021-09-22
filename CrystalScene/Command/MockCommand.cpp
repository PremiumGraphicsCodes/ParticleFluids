#include "MockCommand.h"

#include "Public/MockLabels.h"

using namespace Crystal::Command;

std::string MockCommand::getName()
{
	return MockLabels::MockCommandLabel;
}

bool MockCommand::execute(Crystal::Scene::World* world)
{
	results.value.setValue( args.lhs.getValue() + args.rhs.getValue() );
	return true;
}