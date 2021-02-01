#pragma once

#include "../../CrystalViewer/Command/ICommand.h"

namespace Crystal {
	namespace Physics {

class MeshBoundarySceneCreateCommand : public Command::ICommand
{
public:
	struct Args : Command::IArgs
	{
		Args() {}
	};

	struct Results : Command::IResults
	{
		Command::Result<int> newId;

		Results();
	};

	static std::string getName();

	std::string getCommandName() const { return getName(); }

	MeshBoundarySceneCreateCommand();

	bool execute(Scene::World* world) override;

private:
	Args args;
	Results results;
};

	}
}