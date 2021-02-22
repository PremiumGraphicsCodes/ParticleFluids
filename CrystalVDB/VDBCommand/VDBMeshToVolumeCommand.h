#pragma once

#include "../../CrystalViewer/Command/ICommand.h"

namespace Crystal {
	namespace VDB {

class VDBMeshToVolumeCommand : public Command::ICommand
{
public:
	struct Args : Command::IArgs
	{
		Args();

		Command::Arg<int> vdbMeshId;
		Command::Arg<double> divideLength;
		Command::Arg<int> vdbVolumeId;
	};

	struct Results : Command::IResults
	{
		Results();
	};

	VDBMeshToVolumeCommand();

	static std::string getName();

	std::string getCommandName() const { return getName(); }

	bool execute(Scene::World* world) override;

private:
	Args args;
	Results results;
};

	}
}