#pragma once

#include "../Command/ICommand.h"

namespace Crystal {
	namespace Command {

class NewCommand : public ICommand
{
public:
	static std::string getName();

	void execute(Scene::World* scene) override;
};
	}
}