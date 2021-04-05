#pragma once

#include "../../CrystalViewer/Command/ICommand.h"

namespace Crystal {
	namespace Physics {

class SPHSurfaceConstructionCommand : public Command::ICommand
{
public:
	struct Args : Command::IArgs
	{
		Command::Arg<int> particleSystemId;
		Command::Arg<int> sparseVolumeId;

		Command::Arg<float> effectLength;
		Command::Arg<float> cellLength;

		Args();
	};

	struct Results : Command::IResults
	{
//		Command::Result<int> newId;

		Results();
	};

	static std::string getName();

	std::string getCommandName() const { return getName(); }

	SPHSurfaceConstructionCommand();

	bool execute(Scene::World* world) override;

private:
	Args args;
	Results results;
};

	}
}