#include "../../Crystal/AppBase/Window.h"
#include "../../Crystal/AppBase/FileMenu.h"
#include "../../Crystal/AppBase/CameraMenu.h"
#include "../../Crystal/AppBase/CtrlMenu.h"

#include "../../Crystal/AppBase/ParticleSystemPanel.h"
#include "../../Crystal/AppBase/WireFramePanel.h"
#include "../../Crystal/AppBase/PolygonMeshPanel.h"

#include "../../Crystal/AppBase/AppearancePanel.h"

#include "../../Crystal/AppBase/ParticleSystemTreeList.h"
#include "../../Crystal/AppBase/WireFrameTreeList.h"
#include "../../Crystal/AppBase/PolygonTreeList.h"
#include "../../Crystal/AppBase/LightTreeList.h"
#include "../../Crystal/AppBase/MaterialTreeList.h"

#include "../../Crystal/UI/Repository.h"
#include "../../Crystal/UI/Canvas.h"
#include "../../Crystal/UI/ObjectRenderer.h"

#include "../../Crystal/Graphics/PerspectiveCamera.h"

#include "SpaceHashButton.h"
#include "IntersectionButton.h"
#include "BooleanButton.h"

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
		}
	};
}


int main(int, char**)
{
	auto camera = new PerspectiveCamera(
		1.0,
		0.5f * Tolerance<float>::getPI(),
		Vector3df(0, 0, 0),
		Vector3df(0, 0, -10.0),
		1.0f, 10.0f
	);

	Repository model;
	Canvas canvas(camera);

	Window window(&model, &canvas);
	if (!window.init()) {
		assert(false);
		return 0;
	}

	window.add(new FileMenu("File", &model, &canvas));
	window.add(new CameraMenu("Camera", &model, &canvas));
	window.add(new CtrlMenu("Ctrl", &model, &canvas));

	window.add(new ParticleSystemPanel("ParticleSystem", &model, &canvas));
	window.add(new WireFramePanel("WireFrame", &model, &canvas));
	window.add(new PolygonMeshPanel("Polygon", &model, &canvas));
	window.add(new AppearancePanel("Appearance", &model, &canvas));

	window.add(new ParticleSystemTreeList("ParticleSystems", &model, &canvas));
	window.add(new WireFrameTreeList("WireFrames", &model, &canvas));
	window.add(new PolygonTreeList("Polygons", &model, &canvas));
	window.add(new LightTreeList("Lights", &model, &canvas));
	window.add(new MaterialTreeList("Materials", &model, &canvas));

	window.add(new AlgoPanel("Algo", &model, &canvas));

	window.show();

	return 0;
}
