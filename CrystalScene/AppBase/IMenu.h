#pragma once

#include "IWindow.h"

namespace Crystal {
	namespace Scene {
		class World;
	}
	namespace UI {
		class Canvas;

class IMenu : public IWindow
{
public:
	IMenu(const std::string& name, Scene::World* model, Canvas* canvas) :
		IWindow(name),
		model(model),
		canvas(canvas)
	{}

	virtual ~IMenu() {};

protected:
	Scene::World* getWorld() { return model; }

	Canvas* getCanvas() { return canvas; }

private:
	Scene::World* model;
	Canvas* canvas;
};
	}
}