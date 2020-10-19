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

		Args();
	};

	struct Results : Command::IResults
	{
		Command::Result<int> newId;

		Results();
	};

	static std::string getName();

	FluidSceneCreateCommand();

	bool execute(Scene::World* world) override;

private:
	Args args;
	Results results;
};

	}
}