#pragma once

#include "ICommand.h"

namespace Crystal {
	namespace Command {

class CameraFitCommand : ICommand
{
public:
	void execute(Scene::World* world) override;
};

	}
}