#include "../AppBase/Window.h"
#include "../AppBase/FileMenu.h"
#include "../AppBase/CameraMenu.h"
#include "../AppBase/CtrlMenu.h"

#include "../AppBase/ParticlePanel.h"
#include "../AppBase/WireFramePanel.h"
#include "../AppBase/PolygonPanel.h"

#include "../AppBase/AppearancePanel.h"

#include "../AppBase/ParticleSystemTreeList.h"
#include "../AppBase/LightTreeList.h"
#include "../AppBase/MaterialTreeList.h"

#include "../UI/Model.h"
#include "../UI/Canvas.h"
#include "../UI/Renderer.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::UI;


#include "../Graphics/PerspectiveCamera.h"

int main(int, char**)
{
	auto camera = new PerspectiveCamera(
		1.0,
		0.5f * Tolerance<float>::getPI(),
		Vector3df(0,0,0),
		Vector3df(0,0,-10.0),
		1.0f, 10.0f
		);

	Renderer *renderer = new Renderer(camera);

	Model model;
	Canvas canvas(renderer, camera);

	Window window(&model, &canvas);
	if (!window.init()) {
		assert(false);
		return 0;
	}

	window.add(new FileMenu("File", &model, &canvas));
	window.add(new CameraMenu("Camera", &model, &canvas));
	window.add(new CtrlMenu("Ctrl", &model, &canvas));

	window.add(new ParticlePanel(&model, &canvas));
	window.add(new WireFramePanel(&model, &canvas));
	window.add(new PolygonPanel(&model, &canvas));
	window.add(new AppearancePanel("Appearance", &model, &canvas));

	window.add(new ParticleSystemTreeList("ParticleSystems", &model, &canvas));
	window.add(new LightTreeList("Lights", &model, &canvas));
	window.add(new MaterialTreeList("Materials", &model, &canvas));

	window.show();

	return 0;
}
