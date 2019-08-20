#include "../../Crystal/AppBase/Window.h"
#include "../../Crystal/AppBase/FileMenu.h"
#include "../../Crystal/AppBase/CameraMenu.h"
#include "../../Crystal/AppBase/CtrlMenu.h"
#include "../../Crystal/AppBase/ShapeMenu.h"
#include "../../Crystal/AppBase/AppearanceMenu.h"
#include "../../Crystal/AppBase/SceneListPanel.h"
#include "../../Crystal/AppBase/Canvas.h"
#include "../../Crystal/AppBase/ControlPanel.h"

#include "../../Crystal/Scene/World.h"

#include "AlgoMenu.h"

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
	window.add(new CtrlMenu("Ctrl", &model, &canvas));
	window.add(new ShapeMenu("Shape", &model, &canvas, control));
	window.add(new AppearanceMenu("Appearance", &model, &canvas, control));
	window.add(new AlgoMenu("Algo", &model, &canvas, control));

	window.add(new SceneListPanel("Scene", &model, &canvas, control));


	window.show();

	return 0;
}
