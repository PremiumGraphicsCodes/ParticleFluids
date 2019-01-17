#pragma once

namespace Crystal {
	namespace UI {
		class Model;
		class ICanvas;

class IMenu
{
public:
	IMenu(Model* model, ICanvas* canvas) :
		model(model),
		canvas(canvas)
	{}

	virtual ~IMenu() {};

	virtual void show() {};

protected:
	Model* model;
	ICanvas* canvas;
};
	}
}