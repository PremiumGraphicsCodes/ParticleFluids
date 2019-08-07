#pragma once

#include "IOkCancelView.h"

#include "MaterialView.h"

namespace Crystal {
	namespace UI {

class MaterialAddView : public IOkCancelView
{
public:
	MaterialAddView(const std::string& name, Scene::World* model, Canvas* canvas);

	void show() override;

private:
	void onOk() override;

private:
	MaterialView material;
	StringView name;
};

	}
}