#pragma once

namespace Crystal {
	namespace UI {
		class Model;
		class Canvas;

class IMenu
{
public:
	IMenu(Model* model, Canvas* canvas) :
		model(model),
		canvas(canvas)
	{}

	virtual ~IMenu() {};

	virtual void show() {};

protected:
	Model* model;
	Canvas* canvas;
};
	}
}