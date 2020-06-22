#include "../../CrystalViewer/AppBase/IOkCancelView.h"
#include "../../CrystalViewer/AppBase/ObjectSelectView.h"
#include "../../CrystalViewer/AppBase/DoubleView.h"
#include "../CrystalPhysics/FluidSimulator.h"

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
	Algo::Physics::FluidScene* fluidScene;
	Algo::Physics::FluidSimulator simulator;
	Button startButton;
	Button resetButton;
	Button nextButton;
	int newId;
};

	}
}