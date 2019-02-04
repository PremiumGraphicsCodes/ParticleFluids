#pragma once

#include "IWindow.h"

#include "../UI/Repository.h"
#include "../UI/Canvas.h"

namespace Crystal {
	namespace UI {

class ITreeList : public IWindow
{
protected:
	ITreeList(const std::string& name, Repository* model, Canvas* canvas) :
		IWindow(name),
		model(model),
		canvas(canvas)
	{}

	virtual ~ITreeList()
	{}

protected:
	virtual void onShow() = 0;

	std::string getName() const { return name; }

	Repository* getModel() { return model; }

	Canvas* getCanvas() { return canvas; }

private:
	Repository* model;
	Canvas* canvas;
};

	}
}