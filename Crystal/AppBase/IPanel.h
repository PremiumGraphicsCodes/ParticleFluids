#pragma once

#include "IWindow.h"
#include <list>

namespace Crystal {
	namespace UI {
		class Model;
		class Canvas;

class IPanel : public IWindow
{
public:
	IPanel(const std::string& name, Model* model, Canvas* canvas) :
		IWindow(name),
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