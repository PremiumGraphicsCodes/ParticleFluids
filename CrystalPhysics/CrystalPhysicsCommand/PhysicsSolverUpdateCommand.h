#pragma once

#include "../../CrystalViewer/Command/ICommand.h"

namespace Crystal {
	namespace Physics {

class PhysicsSolverUpdateCommand : public Command::ICommand
{
public:
	struct Args : Command::IArgs
	{
		Command::Arg<int> id;
		Command::Arg<std::vector<int>> fluidSceneIds;
		Command::Arg<std::vector<int>> csgBoundarySceneIds;
		Command::Arg<float> timeStep;
		Command::Arg<std::string> name;

		Args();
	};

	struct Results : Command::IResults
	{
		Results();
	};

	static std::string getName();

	std::string getCommandName() const { return getName(); }

	PhysicsSolverUpdateCommand();

	bool execute(Scene::World* world) override;

private:
	Args args;
	Results results;
};

	}
}