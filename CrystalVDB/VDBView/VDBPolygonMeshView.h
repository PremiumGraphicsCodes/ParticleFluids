#pragma once

#include "../../CrystalViewer/AppBase/IOkCancelView.h"
#include "../../CrystalViewer/AppBase/Sphere3dView.h"

namespace Crystal {
	namespace Physics {
		class KFFluidScene;
	}
	namespace UI {

class VDBPolygonMeshView : public IOkCancelView
{
public:
	VDBPolygonMeshView(const std::string& name, Scene::World* model, Canvas* canvas);

private:
	void onOk() override;

};

	}
}