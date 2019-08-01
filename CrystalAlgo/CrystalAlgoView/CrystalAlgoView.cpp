#include "../../Crystal/AppBase/Window.h"
#include "../../Crystal/AppBase/FileMenu.h"
#include "../../Crystal/AppBase/CameraMenu.h"
#include "../../Crystal/AppBase/CtrlMenu.h"
#include "../../Crystal/AppBase/ShapeMenu.h"
#include "../../Crystal/AppBase/AppearanceMenu.h"

#include "../../Crystal/AppBase/SceneListPanel.h"

#include "../../Crystal/Scene/RootScene.h"
#include "../../Crystal/UI/Canvas.h"
#include "../../Crystal/UI/ObjectRenderer.h"

#include "../../Crystal/Graphics/PerspectiveCamera.h"

#include "SpaceHashButton.h"
#include "IntersectionButton.h"
#include "BooleanButton.h"
#include "MarchingCubesButton.h"
#include "VolumeButton.h"
#include "VolumeConvertButton.h"
#include "../../Crystal/AppBase/ControlPanel.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Scene;
using namespace Crystal::UI;

namespace {
	class AlgoPanel : public IPanel
	{
	public:
		AlgoPanel(const std::string& name, RootScene* repository, Canvas* canvas) :
			IPanel(name, repository, canvas)
		{
			add(new BooleanButton(model, canvas));
			add(new IntersectionButton(model, canvas));
			add(new SpaceHashButton(model, canvas));
			add(new MarchingCubesButton(model, canvas));
			add(new VolumeButton(model, canvas));
			add(new VolumeConvertButton(model, canvas));
		}
	};
}


int main(int, char**)
{
	RootScene model;
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

	//window.add(new SceneAddPanel("SceneAdd", &model, &canvas, control));
	window.add(new SceneListPanel("Scene", &model, &canvas, control));

	window.add(new AlgoPanel("Algo", &model, &canvas));

	window.show();

	return 0;
}
