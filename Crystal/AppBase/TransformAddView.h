#pragma once

#include "IOkCancelView.h"
#include "TransformView.h"
#include "Button.h"

namespace Crystal {
	namespace UI {

class TransformAddView : public IOkCancelView
{
public:
	TransformAddView(const std::string& name, Scene::World* model, Canvas* canvas);

private:
	void onShow() override;

	void onOk() override;

private:
	TransformView transform;
};

	}
}