#include "CrystalScene/AppBase/Window.h"
#include "FileMenu.h"
#include "CrystalScene/AppBase/CameraMenu.h"
#include "CrystalScene/AppBase/CtrlMenu.h"
#include "CrystalScene/AppBase/ShapeMenu.h"
#include "CrystalScene/AppBase/AppearanceMenu.h"
#include "CrystalScene/AppBase/SceneListPanel.h"
#include "CrystalScene/AppBase/Canvas.h"
#include "CrystalScene/AppBase/ControlPanel.h"

#include "CrystalScene/Scene/World.h"

#include "CrystalVDB/VDBCommand/VDBInitCommand.h"

#include "FluidMenu.h"
#include "VDBMenu.h"

#include "MainModel.h"
#include "FluidListPanel.h"
#include "SolverView.h"

#include <iostream>
#include <cassert>

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Scene;
using namespace Crystal::UI;

using namespace Crystal::Shader;


int main()
{
	World world;
	Canvas canvas;

	Window window("FluidStudio", &world, &canvas);
	if (!window.init()) {
		std::cout << "window initialization failed!" << std::endl;
		assert(false);
		return 0;
	}

	Crystal::VDB::VDBInitCommand initCommand;
	if (!initCommand.execute(&world)) {
		std::cout << "VDB initialization failed!" << std::endl;
		assert(false);
		return 0;
	}

	PG::FS::MainModel model(&world);
	model.init();

	auto control = new ControlPanel("Control", &world, &canvas);
	window.add(control);

	window.add(new PG::FS::FileMenu("File", &world, &canvas));
	window.add(new CameraMenu("Camera", &world, &canvas));
	window.add(new CtrlMenu("Ctrl", &world, &canvas));
	window.add(new ShapeMenu("Shape", &world, &canvas, control));
	window.add(new AppearanceMenu("Appearance", &world, &canvas, control));
	window.add(new FluidMenu("Fluid", &world, &canvas, control, &model));
	window.add(new VDBMenu("VDB", &world, &canvas, control));

	//window.add(new SceneListPanel("Scene", &world, &canvas, control));
	window.add(new FluidListPanel("Fluids", &world, &canvas, control, model.getSolver()));

	window.add(new SolverView("Solver", &world, &canvas, model.getSolver()));

	window.show();

	return 0;
}