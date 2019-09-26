#include "Command.h"
#include "CommandFactory.h"

using namespace Crystal::Command;

Command::Command(const std::string& name)
{
	create(name);
}

Command::~Command()
{
	clear();
}

void Command::create(const std::string& name)
{
	command = CommandFactory::create(name);
}

void Command::clear()
{
	command.reset();
}

void Command::setArg(const std::string& name, std::any value)
{
	command->setArg(name, value);
}

void Command::execute(Crystal::Scene::Scene* scene)
{
	command->execute(scene);
}

std::any Command::getResult(const std::string& name)
{
	return command->getResult(name);
}
