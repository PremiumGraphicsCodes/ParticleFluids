#pragma once

#include "CrystalScene/Command/ICommand.h"

namespace Crystal {
	namespace VDB {

class VDBPCDFileWriteCommand : public Command::ICommand
{
public:
	struct Args : Command::IArgs
	{
		Args();

		Command::Arg<std::string> filePath;
		Command::Arg<int> vdbPsId;
	};

	struct Results : Command::IResults
	{
		Results();

		//Command::Result<std::vector<int>> newIds;
	};

	VDBPCDFileWriteCommand();

	explicit VDBPCDFileWriteCommand(const Args& args);

	static std::string getName();

	std::string getCommandName() const { return getName(); }

	bool execute(Scene::World* world) override;

private:
	Args args;
	Results results;
};

	}
}