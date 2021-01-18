#pragma once

#include "../../CrystalViewer/Command/ICommand.h"

namespace Crystal {
	namespace VDB {

class VDBVolumeToPSCommand : public Command::ICommand
{
public:
	struct Args : Command::IArgs
	{
		Args();

		Command::Arg<int> vdbVolumeId;
		Command::Arg<int> vdbParticleSystemId;
		Command::Arg<double> radius;
	};

	struct Results : Command::IResults
	{
		Results();
	};

	VDBVolumeToPSCommand();

	static std::string getName();

	std::string getCommandName() const { return getName(); }

	bool execute(Scene::World* world) override;

private:
	Args args;
	Results results;
};

	}
}