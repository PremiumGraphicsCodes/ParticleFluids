#pragma once

#include <string>
#include <memory>
#include <any>

#include "ICommand.h"

namespace Crystal {
	namespace Command {

class Command
{
public:
	Command() {}

	Command(const std::string& name);

	~Command();

	void create(const std::string& name);

	void clear();

	void setArg(const std::string& name, std::any value);

	void execute(Scene::World* scene);

	std::any getResult(const std::string& name);

private:
	std::unique_ptr<ICommand> command;
};

/*
class SetCommand
{
public:
	SetCommand(const std::string& name);

	void Set(int id, std::any value);
};

class GetCommand
{
public:
	SetCommand(const std::string& name);

	std::any Get(const std::string& name);
}
*/
	}
}