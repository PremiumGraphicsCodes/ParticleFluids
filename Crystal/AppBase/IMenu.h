#pragma once

#include "IWindow.h"

namespace Crystal {
	namespace UI {
		class RootScene;
		class Canvas;

class IMenu : public IWindow
{
public:
	IMenu(const std::string& name, RootScene* model, Canvas* canvas) :
		IWindow(name),
		model(model),
		canvas(canvas)
	{}

	virtual ~IMenu() {};

	virtual void show() {};

protected:
	RootScene* getModel() { return model; }

	Canvas* getCanvas() { return canvas; }

private:
	RootScene* model;
	Canvas* canvas;
};
	}
}