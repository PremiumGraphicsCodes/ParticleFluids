#pragma once

#include "../../CrystalViewer/Command/ICommand.h"

namespace Crystal {
	namespace Physics {

class CSGBoundarySceneUpdateCommand : public Command::ICommand
{
public:
	struct Args : Command::IArgs
	{
		Command::Arg<int> id;
		Command::Arg<Math::Box3dd> bb;
		Command::Arg<std::string> name;

		Args();
	};

	struct Results : Command::IResults
	{

		Results();
	};

	static std::string getName();

	std::string getCommandName() const { return getName(); }

	CSGBoundarySceneUpdateCommand();

	bool execute(Scene::World* world) override;

private:
	Args args;
	Results results;
};

	}
}