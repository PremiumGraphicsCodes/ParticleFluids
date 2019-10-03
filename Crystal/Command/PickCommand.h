#pragma once

#include "ICommand.h"

namespace Crystal {
	namespace Command {

class PickCommand : public ICommand
{
public:
	struct Args : IArgs
	{
		Args();

		Arg<Math::Vector2dd> position;
	};

	struct Results : IResults
	{
		Results();

		Result<int> parentId;
		Result<int> childId;
	};

	PickCommand() :
		ICommand(&args, &results)
	{}

	void execute(Scene::World* world) override;

private:
	Args args;
	Results results;
};

	}
}