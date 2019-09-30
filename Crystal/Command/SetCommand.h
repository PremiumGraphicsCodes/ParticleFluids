#pragma once

#include <string>
#include <any>
#include "../Scene/World.h"

namespace Crystal {
	namespace Command {

class SetCommand
{
public:
	static void Set(Scene::World* world, const std::string& name, std::any value);

	static void Set(Scene::World* world, int id, const std::string& name, std::any value);

	static void Set(Scene::World* world, int parentId, int childId, const std::string& name, std::any value) {}
};

	}
}