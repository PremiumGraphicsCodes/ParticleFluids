#pragma once

#include "ICommand.h"

namespace Crystal {
	namespace Command {

class ClearCommand : public ICommand
{
public:
	struct Args : public IArgs
	{
		Args();

		Arg<int> layer;
	};

	static std::string getName();

	void execute(Scene::World* world) override;

private:
	Args args;
};
	}
}