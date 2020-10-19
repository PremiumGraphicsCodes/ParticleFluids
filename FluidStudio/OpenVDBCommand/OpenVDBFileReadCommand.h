#pragma once

#include "../../CrystalViewer/Command/ICommand.h"

namespace Crystal {
	namespace OpenVDB {

class OpenVDBFileReadCommand : public Command::ICommand
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

	OpenVDBFileReadCommand();

	static std::string getName();

	bool execute(Scene::World* world) override;

private:
	Args args;
	Results results;
};

	}
}