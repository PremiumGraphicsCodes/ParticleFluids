#pragma once

#include "ICommand.h"

namespace Crystal {
	namespace Command {

class BuildCommand : public ICommand
{
public:
	struct Args : public IArgs
	{
		Args();

		Arg<int> id;
		Arg<int> layer;
	};

	static std::string getName();

	BuildCommand();

	bool execute(Scene::World* world) override;

private:
	Args args;
};
	}
}