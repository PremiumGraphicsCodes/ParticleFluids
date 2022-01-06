#pragma once

#include "CrystalScene/Command/ICommand.h"

namespace Crystal {
	namespace VDB {

class VDBVolumeToMeshCommand : public Command::ICommand
{
public:
	struct Args : Command::IArgs
	{
		Args();

		Command::Arg<int> vdbVolumeId;
		Command::Arg<int> vdbMeshId;
		Command::Arg<double> threshold;
		Command::Arg<double> adaptivity;
	};

	struct Results : Command::IResults
	{
		Results();
	};

	VDBVolumeToMeshCommand();

	explicit VDBVolumeToMeshCommand(const Args& args);

	static std::string getName();

	std::string getCommandName() const { return getName(); }

	bool execute(Scene::World* world) override;

private:
	Args args;
	Results results;
};

	}
}