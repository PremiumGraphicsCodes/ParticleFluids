#pragma once

#include "ICommand.h"
#include "../Math/Vector3d.h"
#include <vector>

namespace Crystal {
	namespace Command {

class ParticleSystemAddCommand : public ICommand
{
public:
	struct Args
	{
		std::vector<Math::Vector3dd> positions;
	};

	void execute() override;
};
	}
}