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
	}
}

namespace Crystal {
	namespace UI {
		class FluidModel;

class FluidView : public IOkCancelView
{
public:
	FluidView(const std::string& name, Scene::World* world, Canvas* canvas);

	void setValue(PG::FS::FluidModel* fluid);

private:
	void onOk() override;

	PG::FS::FluidModel* fluid;
	IntView idView;
	IntView particleSystemIdView;
	Box3dView boundaryView;
	FloatView pressureCoeView;
	FloatView viscosityCoeView;
	FloatView heatDiffuseCoeView;
	FloatView dragHeatCoeView;
	FloatView dragForceCoeView;

};
	}
}