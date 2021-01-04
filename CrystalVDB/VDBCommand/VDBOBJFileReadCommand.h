#pragma once

#include "../../CrystalViewer/Command/ICommand.h"

namespace Crystal {
	namespace VDB {

class VDBOBJFileReadCommand : public Command::ICommand
{
public:
	struct Args : Command::IArgs
	{
		Args();

		Command::Arg<std::string> filePath;
	};

	struct Results : Command::IResults
	{
		Results();

		Command::Arg<int> vdbMeshId;
		//Command::Result<std::vector<int>> newIds;
	};

	VDBOBJFileReadCommand();

	static std::string getName();

	std::string getCommandName() const { return getName(); }

	bool execute(Scene::World* world) override;

private:
	Args args;
	Results results;
};

	}
}