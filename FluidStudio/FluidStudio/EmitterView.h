#pragma once

#include "CrystalScene/AppBase/IView.h"
#include "CrystalScene/AppBase/IOkCancelView.h"
#include "CrystalScene/AppBase/Box3dView.h"
#include "CrystalScene/AppBase/FloatView.h"
#include "CrystalScene/AppBase/IntView.h"
#include "CrystalScene/AppBase/Vector3dView.h"

namespace PG {
	namespace FS {
		class EmitterModel;
	}
}

namespace Crystal {
	namespace UI {

class EmitterView : public IOkCancelView
{
public:
	EmitterView(const std::string& name, Scene::World* world, Canvas* canvas);

	void setValue(PG::FS::EmitterModel* emitter);

private:
	void onOk() override;

	PG::FS::EmitterModel* emitter;
	IntView idView;
	IntView psIdView;
	Box3dView boundaryView;
	FloatView pressureCoeView;
	FloatView viscosityCoeView;
	FloatView heatDiffuseCoeView;
	FloatView dragHeatCoeView;
	FloatView dragForceCoeView;
	FloatView temperatureView;
	IntView lifeLimitView;
	Vector3dView velocityView;

};

	}
}