#pragma once

#include "CrystalScene/AppBase/IView.h"
#include "CrystalScene/AppBase/IOkCancelView.h"
#include "CrystalScene/AppBase/Box3dView.h"
#include "CrystalScene/AppBase/FloatView.h"

namespace Crystal {
	namespace UI {
		class EmitterModel;

class EmitterView : public IOkCancelView
{
public:
	EmitterView(const std::string& name, Scene::World* world, Canvas* canvas);

	void setValue(EmitterModel* emitter);

private:
	void onOk() override;

	EmitterModel* emitter;
	Box3dView boundaryView;
	FloatView pressureCoeView;
	FloatView viscosityCoeView;
	FloatView heatDiffuseCoeView;
	FloatView dragHeatCoeView;
	FloatView dragForceCoeView;
};

	}
}