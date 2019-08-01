#pragma once

#include "IPanel.h"
//#include "ShaderView.h"

namespace Crystal {
	namespace UI {

class ShaderAddView : public IPanel
{
public:
	ShaderAddView(const std::string& name, Scene::RootScene* model, Canvas* canvas);

	void show() override;

private:
	//ShaderView shader;
};

	}
}
