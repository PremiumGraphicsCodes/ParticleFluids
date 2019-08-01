#pragma once

#include "IPanel.h"

#include "MaterialView.h"

namespace Crystal {
	namespace UI {

class MaterialAddView : public IPanel
{
public:
	MaterialAddView(const std::string& name, RootScene* model, Canvas* canvas);

	void show() override;

private:
	void onOk();

private:
	MaterialView material;
	StringView name;
};

	}
}