#include "../../CrystalViewer/AppBase/IOkCancelView.h"
#include "../../CrystalViewer/AppBase/ObjectSelectView.h"
#include "../../CrystalViewer/AppBase/DoubleView.h"
#include "../CrystalPhysics/FluidSimulator.h"

namespace Crystal {
	namespace Physics {
		class PBFluidScene;
		class PBSPHSolver;
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
	Physics::PBSPHSolver* simulator;
	Physics::PBFluidScene* fluidScene;
	Button startButton;
	Button resetButton;
	Button nextButton;
	int newId;
};

	}
}