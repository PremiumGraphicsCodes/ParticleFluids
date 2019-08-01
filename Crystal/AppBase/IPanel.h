#pragma once

#include "IWindow.h"
#include <list>

namespace Crystal {
	namespace Scene {
		class RootScene;
	}
	namespace UI {
		class Canvas;

class IPanel : public IWindow
{
public:
	IPanel(const std::string& name, Scene::RootScene* model, Canvas* canvas) :
		IWindow(name),
		model(model),
		canvas(canvas)
	{}

	virtual ~IPanel() {};

	virtual void show() override;

protected:
	Scene::RootScene* getRepository() { return model; }

	Canvas* getCanvas() { return canvas; }

	Scene::RootScene* model;

	Canvas* canvas;
};

	}
}