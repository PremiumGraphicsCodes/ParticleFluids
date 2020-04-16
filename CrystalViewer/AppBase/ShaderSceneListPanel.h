#pragma once

#include "IPanel.h"

namespace Crystal {
	namespace Scene {
		class IShaderScene;
	}
	namespace UI {

class ShaderSceneListPanel : public IPanel
{
public:
	ShaderSceneListPanel(const std::string& name, Scene::World* model, Canvas* canvas, IPanel* control);

	void onShow() override;

private:
	void show(Scene::IShaderScene* scene);

	IPanel* control;
};

	}
}