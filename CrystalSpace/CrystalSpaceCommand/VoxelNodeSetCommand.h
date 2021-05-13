#pragma once

#include "../../CrystalViewer/Command/ICommand.h"
#include <vector>

namespace Crystal {
	namespace Space {

class VoxelNodeSetCommand : public Command::ICommand
{
public:
	VoxelNodeSetCommand() :
		Command::ICommand(&args, &results)
	{}

	struct Args : Command::IArgs
	{
		Args();

		Command::Arg< int > voxelId;
		Command::Arg< std::vector<int> > indicesX;
		Command::Arg< std::vector<int> > indicesY;
		Command::Arg< std::vector<int> > indicesZ;
		Command::Arg< std::vector<bool> > values;
	};

	struct Results : Command::IResults
	{
		Results();

		//		Command::Result<int> newId;
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