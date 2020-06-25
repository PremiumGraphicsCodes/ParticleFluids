#include "../../CrystalViewer/AppBase/IOkCancelView.h"
#include "../../CrystalViewer/AppBase/ObjectSelectView.h"
#include "../../CrystalViewer/AppBase/DoubleView.h"
#include "../CrystalPhysics/CSPHSolver.h"

namespace Crystal {
	namespace UI {

class CSPHFluidSimulationView : public IOkCancelView
{
public:
	CSPHFluidSimulationView(Scene::World* model, Canvas* canvas);

private:
	void onOk() override;

	void reset();

private:
//			Algo::Physics::FluidScene* fluidScene;
	Physics::CSPHSolver simulator;
	Button startButton;
	Button resetButton;
	Button nextButton;
	int newId;
};

	}
}