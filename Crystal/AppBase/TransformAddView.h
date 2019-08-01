#pragma once

#include "IOkCancelView.h"
#include "TransformView.h"
#include "Button.h"

namespace Crystal {
	namespace UI {

class TransformAddView : public IOkCancelView
{
public:
	TransformAddView(const std::string& name, Scene::RootScene* model, Canvas* canvas);

	void show() override;

private:
	void onOk() override;

private:
	TransformView transform;
};

	}
}