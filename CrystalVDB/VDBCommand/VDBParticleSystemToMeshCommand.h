#pragma once

#include "../../CrystalViewer/Command/ICommand.h"

namespace Crystal {
	namespace VDB {

class VDBParticleSystemToMeshCommand : public Command::ICommand
{
public:
	struct Args : Command::IArgs
	{
		Args();

		Command::Arg<int> particleSystemId;
		Command::Arg<int> meshId;
	};

	struct Results : Command::IResults
	{
		Results();
	};

	VDBParticleSystemToMeshCommand();

	static std::string getName();

	std::string getCommandName() const { return getName(); }

	bool execute(Scene::World* world) override;

private:
	Args args;
	Results results;
};

	}
}