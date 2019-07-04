#pragma once

#include "IPanel.h"

namespace Crystal {
	namespace Scene {
		class IScene;
	}
	namespace UI {

class ScenePanel : public IPanel
{
public:
	ScenePanel(const std::string& name, Repository* model, Canvas* canvas, IPanel* control);

	void show() override;

private:
	void show(Scene::IScene* scene);

	IPanel* control;
};

	}
}