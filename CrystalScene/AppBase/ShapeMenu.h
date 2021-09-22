#pragma once

#include "IMenu.h"

namespace Crystal {
	namespace UI {
		class ControlPanel;

class PSGenerationMenu : public IMenu
{
public:
	PSGenerationMenu(const std::string& name, Scene::World* world, Canvas* canvas, ControlPanel* control);

	void onShow() override;

private:
	ControlPanel* control;
};

class WFGenerationMenu : public IMenu
{
public:
	WFGenerationMenu(const std::string& name, Scene::World* world, Canvas* canvas, ControlPanel* control);

	void onShow() override;

private:
	ControlPanel* control;
};

class PMGenerationMenu : public IMenu
{
public:
	PMGenerationMenu(const std::string& name, Scene::World* world, Canvas* canvas, ControlPanel* control);

	void onShow() override;

private:
	ControlPanel* control;
};

class TMGenerationMenu : public IMenu
{
public:
	TMGenerationMenu(const std::string& name, Scene::World* world, Canvas* canvas, ControlPanel* control);

	void onShow() override;

private:
	ControlPanel* control;
};


class VolGenerationMenu : public IMenu
{
public:
	VolGenerationMenu(const std::string& name, Scene::World* world, Canvas* canvas, ControlPanel* control);

	void onShow() override;

private:
	ControlPanel* control;
};

class VoxelGenerationMenu : public IMenu
{
public:
	VoxelGenerationMenu(const std::string& name, Scene::World* world, Canvas* canvas, ControlPanel* control);

	void onShow() override;

private:
	ControlPanel* control;
};

class SolidGenerationMenu : public IMenu
{
public:
	SolidGenerationMenu(const std::string& name, Scene::World* world, Canvas* canvas, ControlPanel* control);

	void onShow() override;

private:
	ControlPanel* control;
};

class TransformMenu : public IMenu
{
public:
	TransformMenu(const std::string& name, Scene::World* world, Canvas* canvas, ControlPanel* control);

	void onShow() override;

private:
	ControlPanel* control;
};

class ShapeMenu : public IMenu
{
public:
	ShapeMenu(const std::string& name, Scene::World* world, Canvas* canvas, ControlPanel* control);

	void onShow() override;

private:
	ControlPanel* control;
	PSGenerationMenu particleSystemMenu;
	WFGenerationMenu wireFrameMenu;
	PMGenerationMenu polygonMeshMenu;
	TMGenerationMenu triangleMeshMenu;
	VolGenerationMenu volMenu;
	VoxelGenerationMenu voxelMenu;
	SolidGenerationMenu solidMenu;
	TransformMenu transformMenu;
};

	}
}