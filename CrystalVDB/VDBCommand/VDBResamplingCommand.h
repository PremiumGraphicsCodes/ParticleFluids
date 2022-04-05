#pragma once

#include "CrystalScene/Command/ICommand.h"

namespace Crystal {
	namespace VDB {

class VDBResamplingCommand : public Command::ICommand
{
public:
	struct Args : Command::IArgs
	{
		Args();

		Command::Arg<int> volumeId;
		Command::Arg<std::string> samplingType;
	};

	struct Results : Command::IResults
	{
		Results();
	};

	VDBResamplingCommand();

	explicit VDBResamplingCommand(const Args& args);

	static std::string getName();

	std::string getCommandName() const { return getName(); }

	bool execute(Scene::World* world) override;

private:
	Args args;
	Results results;
};

	}
}