#pragma once

#include "CrystalScene/Command/ICommand.h"

namespace Crystal {
	namespace Physics {

class SPHSurfaceConstructionCommand : public Command::ICommand
{
public:
	struct Args : Command::IArgs
	{
		Command::Arg<int> particleSystemId;
		//Command::Arg<int> sparseVolumeId;
		Command::Arg<int> triangleMeshId;

		Command::Arg<float> particleRadius;
		Command::Arg<float> threshold;
		Command::Arg<bool> isIsotorpic;

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