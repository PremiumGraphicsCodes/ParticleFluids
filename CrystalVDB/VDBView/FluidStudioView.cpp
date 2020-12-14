#include "../../CrystalViewer/AppBase/Window.h"
#include "../../CrystalViewer/AppBase/FileMenu.h"
#include "../../CrystalViewer/AppBase/CameraMenu.h"
#include "../../CrystalViewer/AppBase/CtrlMenu.h"
#include "../../CrystalViewer/AppBase/ShapeMenu.h"
#include "../../CrystalViewer/AppBase/AppearanceMenu.h"
#include "../../CrystalViewer/AppBase/SceneListPanel.h"
#include "../../CrystalViewer/AppBase/Canvas.h"
#include "../../CrystalViewer/AppBase/ControlPanel.h"

#include "../../Crystal/Scene/World.h"

#include "VDBMenu.h"
#include "SimulationMenu.h"

//#include "PhysicsMenu.h"
#include "TimeLinePanel.h"

#include "../VDBConverter/VDBAdapter.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Scene;
using namespace Crystal::UI;

int main(int, char**)
{
	World model;
	Canvas canvas;

	Window window("FluidStudio", &model, &canvas);
	if (!window.init()) {
		assert(false);
		return 0;
	}
	Crystal::VDB::VDBAdapter::init();
	auto control = new ControlPanel("Control", &model, &canvas);
	window.add(control);

	window.add(new FileMenu("File", &model, &canvas));
	window.add(new CameraMenu("Camera", &model, &canvas));
	window.add(new CtrlMenu("Ctrl", &model, &canvas));
	window.add(new ShapeMenu("Shape", &model, &canvas, control));
	window.add(new AppearanceMenu("Appearance", &model, &canvas, control));
	//window.add(new PhysicsMenu("Physics", &model, &canvas, control));
	window.add(new VDBMenu("OpenVDB", &model, &canvas, control));
	window.add(new SimulationMenu("Simulation", &model, &canvas, control));

	window.add(new SceneListPanel("Scene", &model, &canvas, control));

	window.add(new TimeLinePanel("TimeLine", &model, &canvas));

	window.show();

	return 0;
}

