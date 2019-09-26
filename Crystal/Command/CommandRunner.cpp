#include "CommandRunner.h"

#include "CommandFactory.h"

using namespace Crystal::Command;

namespace {
	std::unique_ptr<ICommand> command;
}

void CommandRunner::create(const std::string& name)
{
	::command = CommandFactory::create(name);
}

void CommandRunner::setArg(const std::string& name, std::any value)
{
//	::command->setArg()
}

void CommandRunner::execute()
{
	::command->execute();
}

std::any CommandRunner::getResult(const std::string& name)
{
	return std::any(0);
}
