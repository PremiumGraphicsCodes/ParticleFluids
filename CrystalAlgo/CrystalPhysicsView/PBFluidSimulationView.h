#include "../../CrystalViewer/AppBase/IOkCancelView.h"
#include "../../CrystalViewer/AppBase/ObjectSelectView.h"
#include "../../CrystalViewer/AppBase/DoubleView.h"
#include "../CrystalPhysics/FluidSimulator.h"

namespace Crystal {
	namespace Physics {
		class PBFluidScene;
	}
	namespace UI {

class PBFluidSimulationView : public IOkCancelView
{
public:
	PBFluidSimulationView(Scene::World* model, Canvas* canvas);

private:
	void onOk() override;

	void reset();

private:
	Algo::Physics::FluidSimulator simulator;
	Physics::PBFluidScene* fluidScene;
	Button startButton;
	Button resetButton;
	Button nextButton;
	int newId;
};

	}
}