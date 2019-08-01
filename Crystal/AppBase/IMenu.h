#pragma once

#include "IWindow.h"

namespace Crystal {
	namespace Scene {
		class RootScene;
	}
	namespace UI {
		class Canvas;

class IMenu : public IWindow
{
public:
	IMenu(const std::string& name, Scene::RootScene* model, Canvas* canvas) :
		IWindow(name),
		model(model),
		canvas(canvas)
	{}

	virtual ~IMenu() {};

	virtual void show() {};

protected:
	Scene::RootScene* getModel() { return model; }

	Canvas* getCanvas() { return canvas; }

private:
	Scene::RootScene* model;
	Canvas* canvas;
};
	}
}