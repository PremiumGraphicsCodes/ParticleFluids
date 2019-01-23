#pragma once

#include "IWindow.h"

namespace Crystal {
	namespace UI {
		class Model;
		class Canvas;

class IPanel : public IWindow
{
public:
	IPanel(Model* model, Canvas* canvas) :
		model(model),
		canvas(canvas)
	{}

	virtual ~IPanel() {};

	virtual void show() = 0;

protected:
	Model* model;
	Canvas* canvas;
};

	}
}