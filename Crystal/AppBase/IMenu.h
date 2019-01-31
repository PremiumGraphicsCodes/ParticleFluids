#pragma once

#include "IWindow.h"

namespace Crystal {
	namespace UI {
		class Model;
		class Canvas;

class IMenu : public IWindow
{
public:
	IMenu(const std::string& name, Model* model, Canvas* canvas) :
		IWindow(name),
		model(model),
		canvas(canvas)
	{}

	virtual ~IMenu() {};

	virtual void show() {};

protected:
	Model* getModel() { return model; }

	Canvas* getCanvas() { return canvas; }

private:
	Model* model;
	Canvas* canvas;
};
	}
}