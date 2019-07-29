#pragma once

#include "IPanel.h"
#include "TransformView.h"
#include "Button.h"

namespace Crystal {
	namespace UI {

class TransformAddView : public IPanel
{
public:
	TransformAddView(const std::string& name, Repository* model, Canvas* canvas);

	void show() override;

private:
	void onOk();

private:
	TransformView transform;
	Button ok;
};

	}
}