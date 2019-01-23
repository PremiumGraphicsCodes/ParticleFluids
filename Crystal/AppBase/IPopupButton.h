#pragma once

#include "../UI/Model.h"
#include "../UI/Canvas.h"

namespace Crystal {
	namespace UI {

class IPopupButton
{
protected:
	IPopupButton(const std::string& name, Model* model, Canvas* canvas) :
		name(name),
		model(model),
		canvas(canvas)
	{}

	virtual void onShow() = 0;

	virtual void onOk() = 0;

	virtual void onCancel() = 0;

	Model* getModel() { return model; }

	Canvas* getCanvas() { return canvas; }

private:
	std::string name;
	Model* model;
	Canvas* canvas;
};
	}
}