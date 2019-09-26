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
	};

	void execute() override {}

private:
	Args args;
	Results results;
};
	}
}