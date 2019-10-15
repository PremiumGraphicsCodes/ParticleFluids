#include "MockCommand.h"

using namespace Crystal::Command;

std::string MockCommand::getName()
{
	return "Mock";
}

void MockCommand::execute(Crystal::Scene::World* world)
{
	results.value.setValue( args.lhs.getValue() + args.rhs.getValue() );
}