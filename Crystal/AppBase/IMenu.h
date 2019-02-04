#pragma once

#include "IWindow.h"

namespace Crystal {
	namespace UI {
		class Repository;
		class Canvas;

class IMenu : public IWindow
{
public:
	IMenu(const std::string& name, Repository* model, Canvas* canvas) :
		IWindow(name),
		model(model),
		canvas(canvas)
	{}

	virtual ~IMenu() {};

	virtual void show() {};

protected:
	Repository* getModel() { return model; }

	Canvas* getCanvas() { return canvas; }

private:
	Repository* model;
	Canvas* canvas;
};
	}
}