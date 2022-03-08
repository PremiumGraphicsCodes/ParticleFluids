#pragma once

#include "IMenu.h"

namespace Crystal {
	namespace UI {
		class ControlPanel;

class VoxelGenerationMenu : public IMenu
{
public:
	VoxelGenerationMenu(const std::string& name, Scene::World* world, Canvas* canvas, ControlPanel* control);
};

class SolidGenerationMenu : public IMenu
{
public:
	SolidGenerationMenu(const std::string& name, Scene::World* world, Canvas* canvas, ControlPanel* control);
};

class TransformMenu : public IMenu
{
public:
	TransformMenu(const std::string& name, Scene::World* world, Canvas* canvas, ControlPanel* control);
};

class ShapeMenu : public IMenu
{
public:
	ShapeMenu(const std::string& name, Scene::World* world, Canvas* canvas, ControlPanel* control);
};

	}
}