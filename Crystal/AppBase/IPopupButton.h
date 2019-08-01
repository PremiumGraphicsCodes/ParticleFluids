#pragma once

#include "IWindow.h"

#include "../Scene/RootScene.h"
#include "../UI/Canvas.h"

namespace Crystal {
	namespace UI {

class IPopupButton : public IWindow
{
protected:
	IPopupButton(const std::string& name, RootScene* model, Canvas* canvas) :
		IWindow(name),
		model(model),
		canvas(canvas)
	{}

	~IPopupButton()
	{}

public:
	void show() override;

protected:
	virtual void onShow() = 0;

	virtual void onOk() = 0;

	virtual void onCancel() = 0;

	RootScene* getModel() { return model; }

	Canvas* getCanvas() { return canvas; }

private:
	RootScene* model;
	Canvas* canvas;
};
	}
}