#pragma once

#include "../../CrystalViewer/Command/ICommand.h"
#include <vector>

namespace Crystal {
	namespace Command {

class VDBParticleSystemCreateCommand : public ICommand
{
public:
	VDBParticleSystemCreateCommand() :
		ICommand(&args, &results)
	{}

	struct Args : IArgs
	{
		Args();

		Arg< std::vector<Math::Vector3dd> > positions;
	};

	struct Results : IResults
	{
		Results();

		Result<int> newId;
	};

	static std::string getName();

	std::string getCommandName() const { return getName(); }

	bool execute(Scene::World* scene) override;

private:
	Args args;
	Results results;
};

	}
}