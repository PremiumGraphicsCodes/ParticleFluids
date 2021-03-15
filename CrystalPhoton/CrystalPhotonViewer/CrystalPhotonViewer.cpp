#include "../../CrystalViewer/AppBase/Window.h"
#include "../../CrystalViewer/AppBase/FileMenu.h"
#include "../../CrystalViewer/AppBase/CameraMenu.h"
#include "../../CrystalViewer/AppBase/MaskMenu.h"
#include "../../CrystalViewer/AppBase/CtrlMenu.h"
#include "../../CrystalViewer/AppBase/ScreenMenu.h"
#include "../../CrystalViewer/AppBase/ShapeMenu.h"
#include "../../CrystalViewer/AppBase/AppearanceMenu.h"
#include "../../CrystalViewer/AppBase/SelectionMenu.h"
#include "../../CrystalViewer/AppBase/SceneListPanel.h"
#include "../../CrystalViewer/AppBase/ControlPanel.h"
#include "../../CrystalViewer/AppBase/Canvas.h"

#include "PhotonMenu.h"

//#include "../../Crystal/Scene/World.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Scene;
using namespace Crystal::UI;

#include <iostream>

int main(int, char**)
{
	World world;
	Canvas canvas;

	Window window("CrystalViewer", &world, &canvas);
	if (!window.init()) {
		assert(false);
		return 0;
	}

	auto control = new ControlPanel("Control", &world, &canvas);
	window.add(control);

	window.add(new FileMenu("File", &world, &canvas));
	window.add(new CameraMenu("Camera", &world, &canvas));
	window.add(new MaskMenu("Mask", &world, &canvas));
	window.add(new CtrlMenu("Ctrl", &world, &canvas));
	window.add(new ScreenMenu("Screen", &world, &canvas));
	window.add(new ShapeMenu("Shape", &world, &canvas, control));
	window.add(new AppearanceMenu("Appearance", &world, &canvas, control));
	window.add(new SelectionMenu("Selection", &world, &canvas, control));
	window.add(new PhotonMenu("Photon", &world, &canvas, control));

	window.add(new SceneListPanel("SceneList", &world, &canvas, control));

	window.show();

	return 0;
}