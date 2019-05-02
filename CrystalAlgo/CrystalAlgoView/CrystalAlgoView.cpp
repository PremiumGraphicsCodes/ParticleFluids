#include "../../Crystal/AppBase/Window.h"
#include "../../Crystal/AppBase/FileMenu.h"
#include "../../Crystal/AppBase/CameraMenu.h"
#include "../../Crystal/AppBase/CtrlMenu.h"

#include "../../Crystal/AppBase/ObjectPanel.h"
#include "../../Crystal/AppBase/AppearancePanel.h"
#include "../../Crystal/AppBase/ShaderPanel.h"

#include "../../Crystal/UI/Repository.h"
#include "../../Crystal/UI/Canvas.h"
#include "../../Crystal/UI/ObjectRenderer.h"

#include "../../Crystal/Graphics/PerspectiveCamera.h"

#include "SpaceHashButton.h"
#include "IntersectionButton.h"
#include "BooleanButton.h"
#include "MarchingCubesButton.h"
#include "VolumeButton.h"
#include "VolumeConverterButton.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::UI;

namespace {
	class AlgoPanel : public IPanel
	{
	public:
		AlgoPanel(const std::string& name, Repository* repository, Canvas* canvas) :
			IPanel(name, repository, canvas)
		{
			add(new BooleanButton(model, canvas));
			add(new IntersectionButton(model, canvas));
			add(new SpaceHashButton(model, canvas));
			add(new MarchingCubesButton(model, canvas));
			add(new VolumeButton(model, canvas));
			add(new VolumeConverterButton(model, canvas));
		}
	};
}


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
	window.add(new CtrlMenu("Ctrl", &model, &canvas));

	window.add(new ObjectPanel("Object", &model, &canvas));
	window.add(new AppearancePanel("Appearance", &model, &canvas));
	window.add(new ShaderPanel("ShaderPanel", &model, &canvas));

	window.add(new AlgoPanel("Algo", &model, &canvas));

	window.show();

	return 0;
}
