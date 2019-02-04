#pragma once

#include "IWindow.h"
#include <list>

namespace Crystal {
	namespace UI {
		class Repository;
		class Canvas;

class IPanel : public IWindow
{
public:
	IPanel(const std::string& name, Repository* model, Canvas* canvas) :
		IWindow(name),
		model(model),
		canvas(canvas)
	{}

	virtual ~IPanel() {};

	virtual void show() override;

protected:
	Repository* model;
	Canvas* canvas;
};

	}
}