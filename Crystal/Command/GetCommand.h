#pragma once

#include <string>
#include <any>
#include "../Scene/World.h"

namespace Crystal {
	namespace Command {

class GetCommand
{
public:
	explicit GetCommand(const std::string& name);

	std::any Get(Scene::World* world);

private:
	const std::string name;
};

	}
}