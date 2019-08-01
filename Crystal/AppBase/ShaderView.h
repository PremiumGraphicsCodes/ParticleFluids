#pragma once

#include "IPanel.h"
#include "../Scene/ShaderScene.h"

namespace Crystal {
	namespace UI {

class ShaderView : public IPanel
{
public:
	ShaderView(const std::string& name, Scene::RootScene* model, Canvas* canvas);

	void show() override;

	void setValue(const Scene::ShaderScene& scene);

private:
	std::string vsSource;
	std::string fsSource;
};

	}
}