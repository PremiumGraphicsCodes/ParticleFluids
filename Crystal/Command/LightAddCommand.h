#pragma once

#include "ICommand.h"

namespace Crystal {
	namespace Command {

class LightAddCommand : ICommand
{
	void execute(Scene::World* world) override {};
};

	}
}