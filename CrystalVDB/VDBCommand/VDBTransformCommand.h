#pragma once

#include "CrystalScene/Command/ICommand.h"

namespace Crystal {
	namespace VDB {

class VDBTransformCommand : public Command::ICommand
{
public:
	struct Args : Command::IArgs
	{
		Args();

		Command::Arg<int> sourceVolumeId;
		Command::Arg<int> targetVolumeId;
		//Command::Arg<int> width;
		//Command::Arg<int> iteration;
	};

	struct Results : Command::IResults
	{
		Results();
	};

	VDBTransformCommand();

	explicit VDBTransformCommand(const Args& args);

	static std::string getName();

	std::string getCommandName() const { return getName(); }

	bool execute(Scene::World* world) override;

private:
	Args args;
	Results results;
};

	}
}