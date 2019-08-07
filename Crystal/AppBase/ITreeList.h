#pragma once

#include "IWindow.h"

#include "../Scene/World.h"
#include "../UI/Canvas.h"

namespace Crystal {
	namespace UI {

class ITreeList : public IWindow
{
protected:
	ITreeList(const std::string& name, RootScene* model, Canvas* canvas) :
		IWindow(name),
		repository(model),
		canvas(canvas)
	{}

	virtual ~ITreeList()
	{}

protected:
	virtual void onShow() = 0;

	std::string getName() const { return name; }

	RootScene* getRepository() { return repository; }

	Canvas* getCanvas() { return canvas; }

private:
	RootScene* repository;
	Canvas* canvas;
};

	}
}