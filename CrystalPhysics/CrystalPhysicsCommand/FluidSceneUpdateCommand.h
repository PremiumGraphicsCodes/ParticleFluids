#pragma once

#include "../../CrystalViewer/Command/ICommand.h"

namespace Crystal {
	namespace Physics {

class FluidSceneUpdateCommand : public Command::ICommand
{
public:
	struct Args : Command::IArgs
	{
		Command::Arg<int> id;
		Command::Arg<int> particleSystemId;
		Command::Arg<float> stiffness;
		Command::Arg<float> viscosity;
		Command::Arg<bool> isBoundary;
		Command::Arg<std::string> name;

		Args();
	};

	struct Results : Command::IResults
	{
		Results();
	};

	static std::string getName();

	std::string getCommandName() const { return getName(); }

	FluidSceneUpdateCommand();

	bool execute(Scene::World* world) override;

private:
	Args args;
	Results results;
};

	}
}