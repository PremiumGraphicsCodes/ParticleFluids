#pragma once

#include "IMenu.h"

namespace Crystal {
	namespace UI {
		class ControlPanel;

class PCGenerationMenu : public IMenu
{
public:
	PCGenerationMenu(const std::string& name, Scene::World* world, Canvas* canvas, ControlPanel* control):
		IMenu(name, world, canvas),
		control(control)
	{}

	void onShow() override;

private:
	ControlPanel* control;
};

class WFGenerationMenu : public IMenu
{
public:
	WFGenerationMenu(const std::string& name, Scene::World* world, Canvas* canvas, ControlPanel* control) :
		IMenu(name, world, canvas),
		control(control)
	{}

	void onShow() override;

private:
	ControlPanel* control;
};

class PMGenerationMenu : public IMenu
{
public:
	PMGenerationMenu(const std::string& name, Scene::World* world, Canvas* canvas, ControlPanel* control) :
		IMenu(name, world, canvas),
		control(control)
	{}

	void onShow() override;

private:
	ControlPanel* control;

};

class ShapeMenu : public IMenu
{
public:
	ShapeMenu(const std::string& name, Scene::World* world, Canvas* canvas, ControlPanel* control) :
		IMenu(name, world, canvas),
		control(control),
		pointCloudMenu("PointCloud", world, canvas, control),
		wireFrameMenu("WireFrame", world, canvas, control),
		polygonMeshMenu("PolygonMesh", world, canvas, control)
	{}

	void onShow() override;

private:
	ControlPanel* control;
	PCGenerationMenu pointCloudMenu;
	WFGenerationMenu wireFrameMenu;
	PMGenerationMenu polygonMeshMenu;
};

	}
}