#pragma once

#include "CrystalScene/AppBase/IPanel.h"

namespace Crystal {
	namespace Scene {
		class IScene;
	}
	namespace UI {

class FluidListPanel : public IPanel
{
public:
	FluidListPanel(const std::string& name, Scene::World* model, Canvas* canvas, IPanel* control);

	void onShow() override;

private:
	void show(Scene::IScene* scene);

	IPanel* control;
};

	}
}