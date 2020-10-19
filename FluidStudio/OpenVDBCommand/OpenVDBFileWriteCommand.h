#pragma once

#include "../../CrystalViewer/Command/ICommand.h"

namespace Crystal {
	namespace OpenVDB {

class OpenVDBFileWriteCommand : public Command::ICommand
{
public:
	struct Args : Command::IArgs
	{
		Args();

		Command::Arg<std::string> filePath;
		Command::Arg<int> particleSystemId;
	};

	struct Results : Command::IResults
	{
		Results();

		//Command::Result<std::vector<int>> newIds;
	};

	OpenVDBFileWriteCommand();

	static std::string getName();

	std::string getCommandName() const { return getName(); }

	bool execute(Scene::World* world) override;

private:
	Args args;
	Results results;
};

	}
}