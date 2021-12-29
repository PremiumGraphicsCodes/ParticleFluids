#pragma once

#include "CrystalScene/Command/ICommand.h"
#include <vector>

namespace Crystal {
	namespace Command {

class VDBSceneCreateCommand : public ICommand
{
public:
	VDBSceneCreateCommand() :
		ICommand(&args, &results)
	{}

	struct Args : IArgs
	{
		Arg<std::string> sceneType;
		Arg<std::string> name;
		Arg<std::vector<Math::Vector3dd>> positions;
		
		Args();
	};

	struct Results : IResults
	{
		Results();

		Result<int> newId;
	};

	static std::string getName();

	std::string getCommandName() const { return getName(); }

	bool execute(Scene::World* scene) override;

private:
	Args args;
	Results results;
};

	}
}