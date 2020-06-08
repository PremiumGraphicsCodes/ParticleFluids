#include "../../CrystalViewer/AppBase/IOkCancelView.h"
#include "../../CrystalViewer/AppBase/ObjectSelectView.h"
#include "../../CrystalViewer/AppBase/DoubleView.h"
#include "../CrystalPhysics/FluidSimulator.h"

namespace Crystal {
	namespace UI {

class FluidSimulationView : public IOkCancelView
{
public:
	FluidSimulationView(Scene::World* model, Canvas* canvas);

private:
	void onOk() override;

private:
	Algo::Physics::FluidSimulator simulator;
	Button startButton;
	Button nextButton;
	int newId;

	//ObjectSelectView mesh1;
	//ObjectSelectView mesh2;
	//DoubleView tolerance;
	//bool isUnderSimulation;
};

	}
}