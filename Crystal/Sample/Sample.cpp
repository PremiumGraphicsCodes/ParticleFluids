#include "../AppBase/Window.h"
#include "../AppBase/FileMenu.h"
#include "../AppBase/CameraMenu.h"
#include "../AppBase/CtrlMenu.h"
#include "../AppBase/ScreenMenu.h"

#include "../AppBase/ParticleSystemPanel.h"
#include "../AppBase/WireFramePanel.h"
#include "../AppBase/PolygonMeshPanel.h"
#include "../AppBase/AppearancePanel.h"
#include "../AppBase/ShaderPanel.h"
#include "../AppBase/SelectionPanel.h"
#include "../AppBase/TransformPanel.h"

#include "../AppBase/LightTreeList.h"
#include "../AppBase/MaterialTreeList.h"
#include "../AppBase/ImageTreeList.h"
#include "../AppBase/TextureTreeList.h"

#include "../UI/Repository.h"
#include "../UI/Canvas.h"
#include "../UI/ObjectRenderer.h"

#include "../Graphics/PerspectiveCamera.h"

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
	window.add(new CtrlMenu("Ctrl", &model, &canvas));
	window.add(new ScreenMenu("Screen", &model, &canvas));

	window.add(new ParticleSystemPanel("Particle", &model, &canvas));
	window.add(new WireFramePanel("WireFrame", &model, &canvas));
	window.add(new PolygonMeshPanel("Polygon", &model, &canvas));

	window.add(new AppearancePanel("Appearance", &model, &canvas));
	window.add(new ShaderPanel("ShaderPanel", &model, &canvas));

	window.add(new SelectionPanel("Selection", &model, &canvas));
	window.add(new TransformPanel("Transform", &model, &canvas));


	window.show();

	return 0;
}
