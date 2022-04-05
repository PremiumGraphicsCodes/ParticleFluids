#pragma once

#include "CrystalScene/Command/ICommand.h"

namespace Crystal {
	namespace VDB {

class VDBCompositeCommand : public Command::ICommand
{
public:
	struct Args : Command::IArgs
	{
		Args();

		Command::Arg<int> volumeId1;
		Command::Arg<int> volumeId2;
		Command::Arg<std::string> compositeType;
	};

	struct Results : Command::IResults
	{
		Results();
	};

	VDBCompositeCommand();

	explicit VDBCompositeCommand(const Args& args);

	static std::string getName();

	std::string getCommandName() const { return getName(); }

	bool execute(Scene::World* world) override;

private:
	Args args;
	Results results;
};

	}
}