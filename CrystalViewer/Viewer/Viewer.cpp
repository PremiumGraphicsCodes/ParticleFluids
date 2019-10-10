#include "../AppBase/Window.h"
#include "../AppBase/FileMenu.h"
#include "../AppBase/CameraMenu.h"
#include "../AppBase/MaskMenu.h"
#include "../AppBase/CtrlMenu.h"
#include "../AppBase/ScreenMenu.h"
#include "../AppBase/ShapeMenu.h"
#include "../AppBase/AppearanceMenu.h"
#include "../AppBase/SelectionMenu.h"

#include "../AppBase/SceneListPanel.h"
#include "../AppBase/ControlPanel.h"

#include "../AppBase/Canvas.h"

#include "../../Crystal/Scene/World.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Scene;
using namespace Crystal::UI;

int main(int, char**)
{
	World model;
	Canvas canvas;

	Window window(&model, &canvas);
	if (!window.init()) {
		assert(false);
		return 0;
	}

	auto control = new ControlPanel("Control", &model, &canvas);
	window.add(control);

	window.add(new FileMenu("File", &model, &canvas));
	window.add(new CameraMenu("Camera", &model, &canvas));
	window.add(new MaskMenu("Mask", &model, &canvas));
	window.add(new CtrlMenu("Ctrl", &model, &canvas));
	window.add(new ScreenMenu("Screen", &model, &canvas));
	window.add(new ShapeMenu("Shape", &model, &canvas, control));
	window.add(new AppearanceMenu("Appearance", &model, &canvas, control));
	window.add(new SelectionMenu("Selection", &model, &canvas, control));

	window.add(new SceneListPanel("SceneList", &model, &canvas, control));

	window.show();

	return 0;
}
