#pragma once

#include "ICommand.h"
#include "../Math/Vector3d.h"
#include <vector>

namespace Crystal {
	namespace Command {

class ParticleSystemAddCommand : public ICommand
{
public:
	ParticleSystemAddCommand() :
		ICommand(&args, &results)
	{}

	struct Args : IArgs
	{
		std::vector<Math::Vector3dd> positions;
	};

	struct Results : IResults
	{
		Results() :
			generatedId("GeneratedId", -1)
		{
			add(&generatedId);
		}

		Result<int> generatedId;
	};

	void execute(Scene::World* scene) override;

private:
	Args args;
	Results results;
};
	}
}