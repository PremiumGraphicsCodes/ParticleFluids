#pragma once

#include "../../CrystalViewer/Command/ICommand.h"

namespace Crystal {
	namespace OpenVDB {

class OpenVDBFileReadCommand : Command::ICommand
{
	struct Args : Command::IArgs
	{
		Args();

		Command::Arg<std::string> filePath;
	};

	struct Results : Command::IResults
	{
		Results();

		Command::Result<int> newId;
	};

	OpenVDBFileReadCommand();

	static std::string getName();

	bool execute(Scene::World* world) override;

private:
	Args args;
	Results results;
};
	}
}