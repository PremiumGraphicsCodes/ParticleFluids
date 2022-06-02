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

class EmitterView : public Crystal::UI::IOkCancelView
{
public:
	EmitterView(const std::string& name, Crystal::Scene::World* world, Crystal::UI::Canvas* canvas);

	void setValue(PG::FS::EmitterModel* emitter);

private:
	void onOk() override;

	PG::FS::EmitterModel* emitter;
	Crystal::UI::IntView idView;
	Crystal::UI::IntView psIdView;
	Crystal::UI::Box3dView boundaryView;
	Crystal::UI::FloatView pressureCoeView;
	Crystal::UI::FloatView viscosityCoeView;
	Crystal::UI::FloatView heatDiffuseCoeView;
	Crystal::UI::FloatView dragHeatCoeView;
	Crystal::UI::FloatView dragForceCoeView;
	Crystal::UI::FloatView temperatureView;
	Crystal::UI::IntView lifeLimitView;
	Crystal::UI::Vector3dView velocityView;

};

	}
}