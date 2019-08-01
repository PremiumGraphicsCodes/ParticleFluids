#pragma once

#include "IPanel.h"
#include "TransformView.h"

namespace Crystal {
	namespace UI {

class ShaderAddView : public IPanel
{
public:
	ShaderAddView(const std::string& name, RootScene* model, Canvas* canvas);

	void show() override;

private:
	TransformView transform;
};

	}
}
