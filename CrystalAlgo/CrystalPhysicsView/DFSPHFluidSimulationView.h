#include "../../CrystalViewer/AppBase/IOkCancelView.h"
#include "../../CrystalViewer/AppBase/ObjectSelectView.h"
#include "../../CrystalViewer/AppBase/DoubleView.h"
#include "../../CrystalViewer/AppBase/Box3dView.h"

namespace Crystal {
	namespace Physics {
		class DFFluidScene;
		class DFFluidSolver;
	}
	namespace UI {

class DFSPHFluidSimulationView : public IOkCancelView
{
public:
	DFSPHFluidSimulationView(Scene::World* model, Canvas* canvas);

private:
	void onOk() override;

	void reset();

private:
	Physics::DFFluidSolver* simulator;
	Physics::DFFluidScene* fluidScene;
	Button startButton;
	Button resetButton;
	DoubleView timeStepView;
	DoubleView viscosityCoeView;
	Box3dView boundaryView;
	int newId;
};

	}
}