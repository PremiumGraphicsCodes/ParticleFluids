#include "../AppBase/Window.h"
#include "../AppBase/FileMenu.h"
#include "../AppBase/CameraMenu.h"
#include "../AppBase/MaskMenu.h"
#include "../AppBase/CtrlMenu.h"
#include "../AppBase/ScreenMenu.h"

#include "../AppBase/ObjectPanel.h"
#include "../AppBase/AppearancePanel.h"
#include "../AppBase/SelectionPanel.h"
#include "../AppBase/TransformPanel.h"

#include "../AppBase/ScenePanel.h"
#include "../AppBase/ControlPanel.h"

#include "../UI/Repository.h"
#include "../UI/Canvas.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::UI;



int main(int, char**)
{
	Repository model;
	Canvas canvas;

	Window window(&model, &canvas);
	if (!window.init()) {
		assert(false);
		return 0;
	}

	window.add(new FileMenu("File", &model, &canvas));
	window.add(new CameraMenu("Camera", &model, &canvas));
	window.add(new MaskMenu("Mask", &model, &canvas));
	window.add(new CtrlMenu("Ctrl", &model, &canvas));
	window.add(new ScreenMenu("Screen", &model, &canvas));

	window.add(new ObjectPanel("Object", &model, &canvas));
	window.add(new AppearancePanel("Appearance", &model, &canvas));

	window.add(new SelectionPanel("Selection", &model, &canvas));
	window.add(new TransformPanel("Transform", &model, &canvas));

	auto control = new ControlPanel("Control", &model, &canvas);
	window.add(control);

	window.add(new ScenePanel("Scene", &model, &canvas, control));

	window.show();

	return 0;
}
