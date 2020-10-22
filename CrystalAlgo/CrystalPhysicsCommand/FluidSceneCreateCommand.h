#pragma once

#include "../../CrystalViewer/Command/ICommand.h"

namespace Crystal {
	namespace Physics {

class FluidSceneCreateCommand : public Command::ICommand
{
public:
	struct Args : Command::IArgs
	{
		Command::Arg<int> particleSystemId;
		Command::Arg<std::string> name;

		Args();
	};

	struct Results : Command::IResults
	{
		Command::Result<int> newId;

		Results();
	};

	static std::string getName();

	std::string getCommandName() const { return getName(); }

	FluidSceneCreateCommand();

	bool execute(Scene::World* world) override;

private:
	Args args;
	Results results;
};

	}
}