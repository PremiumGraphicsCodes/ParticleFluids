#pragma once

#include "IWindow.h"
#include <list>

namespace Crystal {
	namespace UI {
		class RootScene;
		class Canvas;

class IPanel : public IWindow
{
public:
	IPanel(const std::string& name, RootScene* model, Canvas* canvas) :
		IWindow(name),
		model(model),
		canvas(canvas)
	{}

	virtual ~IPanel() {};

	virtual void show() override;

protected:
	RootScene* getRepository() { return model; }
	Canvas* getCanvas() { return canvas; }


	RootScene* model;
	Canvas* canvas;
};

	}
}