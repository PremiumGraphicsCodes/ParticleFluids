#pragma once

#include "../../CrystalViewer/Command/ICommand.h"

namespace Crystal {
	namespace OpenVDB {

class OpenVDBInitCommand : public Command::ICommand
{
public:
	struct Args : public Command::IArgs
	{
		Args();
	};

	struct Results : public Command::IResults
	{
		Results();
	};

	OpenVDBInitCommand();

	static std::string getName();

	std::string getCommandName() const { return getName(); }

	bool execute(Scene::World* world) override;

private:
	Args args;
	Results results;
};

	}
}