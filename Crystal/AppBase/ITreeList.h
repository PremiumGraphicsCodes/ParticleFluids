#pragma once

#include "IWindow.h"

#include "../UI/Model.h"
#include "../UI/Canvas.h"

namespace Crystal {
	namespace UI {

class ITreeList : public IWindow
{
protected:
	ITreeList(const std::string& name, Model* model, Canvas* canvas) :
		name(name),
		model(model),
		canvas(canvas)
	{}

	virtual ~ITreeList()
	{}

protected:
	virtual void onShow() = 0;

	std::string getName() const { return name; }

	Model* getModel() { return model; }

	Canvas* getCanvas() { return canvas; }

private:
	std::string name;
	Model* model;
	Canvas* canvas;
};

	}
}