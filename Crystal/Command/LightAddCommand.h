#pragma once

#include "ICommand.h"

namespace Crystal {
	namespace Command {

class LightAddCommand : ICommand
{
public:
	void execute(Scene::World* world) override;
};

	}
}