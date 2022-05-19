#pragma once

#include "CrystalScene/AppBase/IPanel.h"

namespace PG {
	namespace FS {
		class SolverModel;

class FluidListPanel : public Crystal::UI::IPanel
{
public:
	FluidListPanel(const std::string& name, Crystal::Scene::World* model, Crystal::UI::Canvas* canvas, IPanel* control, PG::FS::SolverModel* solver);

	void onShow() override;

private:
	IPanel* control;
	PG::FS::SolverModel* solver;
};

	}
}