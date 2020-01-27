#pragma once

#include "../Command/ICommand.h"

namespace Crystal {
	namespace Command {

class NewCommand : public ICommand
{
public:
	static std::string getName();

	bool execute(Scene::World* scene) override;
};
	}
}