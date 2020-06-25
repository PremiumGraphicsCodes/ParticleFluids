#include "../../CrystalViewer/AppBase/IOkCancelView.h"
#include "../../CrystalViewer/AppBase/ObjectSelectView.h"
#include "../../CrystalViewer/AppBase/DoubleView.h"
#include "../CrystalPhysics/KFFluidSolver.h"

namespace Crystal {
	namespace Algo {
		namespace Physics {
			class FluidScene;
		}
	}
	namespace UI {

class FluidSimulationView : public IOkCancelView
{
public:
	FluidSimulationView(Scene::World* model, Canvas* canvas);

private:
	void onOk() override;

	void reset();

private:
	Physics::FluidScene* fluidScene;
	Physics::KFFluidSolver simulator;
	Button startButton;
	Button resetButton;
	Button nextButton;
	int newId;
};

	}
}