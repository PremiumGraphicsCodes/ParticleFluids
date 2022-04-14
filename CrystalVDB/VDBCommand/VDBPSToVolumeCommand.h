#pragma once

#include "CrystalScene/Command/ICommand.h"

namespace Crystal {
	namespace VDB {

class VDBPSToVolumeCommand : public Command::ICommand
{
public:
	struct Args : Command::IArgs
	{
		Args();

		Command::Arg<int> particleSystemId;
		Command::Arg<int> vdbVolumeId;
		Command::Arg<double> radius;
		Command::Arg<double> voxelSize;
		Command::Arg<bool> doUseSph;
	};

	struct Results : Command::IResults
	{
		Results();
	};

	VDBPSToVolumeCommand();

	explicit VDBPSToVolumeCommand(const Args& args);

	static std::string getName();

	std::string getCommandName() const { return getName(); }

	bool execute(Scene::World* world) override;

private:
	Args args;
	Results results;
};

	}
}