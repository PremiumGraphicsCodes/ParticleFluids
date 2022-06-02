#pragma once

#include "CrystalScene/AppBase/IView.h"
#include "CrystalScene/AppBase/IOkCancelView.h"
#include "CrystalScene/AppBase/Box3dView.h"
#include "CrystalScene/AppBase/IntView.h"
#include "CrystalScene/AppBase/FloatView.h"

#include "MainModel.h"

namespace PG {
	namespace FS {
		class FluidModel;

class FluidView : public Crystal::UI::IOkCancelView
{
public:
	FluidView(const std::string& name, Crystal::Scene::World* world, Crystal::UI::Canvas* canvas);

	void setValue(PG::FS::FluidModel* fluid);

private:
	void onOk() override;

	PG::FS::FluidModel* fluid;
	Crystal::UI::IntView idView;
	Crystal::UI::IntView particleSystemIdView;
	Crystal::UI::Box3dView boundaryView;
	Crystal::UI::FloatView pressureCoeView;
	Crystal::UI::FloatView viscosityCoeView;
	Crystal::UI::FloatView heatDiffuseCoeView;
	Crystal::UI::FloatView dragHeatCoeView;
	Crystal::UI::FloatView dragForceCoeView;

};
	}
}