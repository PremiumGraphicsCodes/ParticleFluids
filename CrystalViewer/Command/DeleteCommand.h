#pragma once

#include "ICommand.h"

namespace Crystal {
	namespace Command {

class DeleteCommand : public ICommand
{
public:
	struct Args : IArgs
	{
		Args();

		Arg<int> sceneId;
	};

	static std::string getName();

	DeleteCommand();

	void execute(Scene::World* world) override;

private:
	Args args;
};
	}
}