#pragma once

#include "IPanel.h"

namespace Crystal {
	namespace Scene {
		class IScene;
	}
	namespace UI {

class SceneListPanel : public IPanel
{
public:
	SceneListPanel(const std::string& name, Scene::RootScene* model, Canvas* canvas, IPanel* control);

	void show() override;

private:
	void show(Scene::IScene* scene);

	IPanel* control;
};

	}
}