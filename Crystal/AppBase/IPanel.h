#pragma once

namespace Crystal {
	namespace UI {
		class Model;
		class ICanvas;

class IPanel
{
public:
	IPanel(Model* model, ICanvas* canvas) :
		model(model),
		canvas(canvas)
	{}

	virtual ~IPanel() {};

	virtual void show() = 0;

protected:
	Model* model;
	ICanvas* canvas;
};

	}
}