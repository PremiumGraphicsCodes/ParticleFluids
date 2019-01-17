#pragma once

#include <vector>
#include <memory>
#include "IMenu.h"
#include "IPanel.h"

struct GLFWwindow;

namespace Crystal {
	namespace UI {

class Window
{
public:
	Window(Model* model, Canvas* canvas);

	bool init();

	void show();

	void add(IMenu* menu) { this->menus.push_back( menu); }

	void add(IPanel* panel) { this->panels.push_back( panel); }

private:
	Model* model;
	Canvas* canvas;
	std::vector< IMenu* > menus;
	std::vector< IPanel* > panels;
	GLFWwindow* window;
};
	}
}