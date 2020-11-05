#pragma once

#include "../../CrystalViewer/Command/ICommand.h"

namespace Crystal {
	namespace Physics {

class CSGBoundarySceneCreateCommand : public Command::ICommand
{
public:
	struct Args : Command::IArgs
	{
		Command::Arg<Math::Box3d> box;
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

	CSGBoundarySceneCreateCommand();

	bool execute(Scene::World* world) override;

private:
	Args args;
	Results results;
};

	}
}