#pragma once

#include "CrystalScene/Command/ICommand.h"

namespace Crystal {
	namespace VDB {

class VDBPCDFileReadCommand : public Command::ICommand
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

		Command::Result<int> vdbPsId;
		//Command::Result<std::vector<int>> newIds;
	};

	VDBPCDFileReadCommand();

	explicit VDBPCDFileReadCommand(const Args& args);

	static std::string getName();

	std::string getCommandName() const { return getName(); }

	bool execute(Scene::World* world) override;

private:
	Args args;
	Results results;
};

	}
}