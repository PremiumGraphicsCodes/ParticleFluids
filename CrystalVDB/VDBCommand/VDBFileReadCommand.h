#pragma once

#include "../../CrystalViewer/Command/ICommand.h"

namespace Crystal {
	namespace VDB {

class VDBFileReadCommand : public Command::ICommand
{
public:
	struct Args : public Command::IArgs
	{
		Args();

		Command::Arg<std::string> filePath;
	};

	struct Results : public Command::IResults
	{
		Results();

		Command::Result<std::vector<int>> newIds;
	};

	VDBFileReadCommand();

	static std::string getName();

	std::string getCommandName() const { return getName(); }

	bool execute(Scene::World* world) override;

private:
	Args args;
	Results results;
};

	}
}