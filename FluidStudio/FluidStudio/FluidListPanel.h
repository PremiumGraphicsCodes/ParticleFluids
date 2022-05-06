#pragma once

#include "CrystalScene/AppBase/IPanel.h"

namespace Crystal {
	namespace Scene {
		class IScene;
	}
	namespace UI {
		class SolverModel;

class FluidListPanel : public IPanel
{
public:
	FluidListPanel(const std::string& name, Scene::World* model, Canvas* canvas, IPanel* control, SolverModel* solver);

	void onShow() override;

private:
	IPanel* control;
	SolverModel* solver;
};

	}
}