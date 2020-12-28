#pragma once

#include "../../CrystalViewer/AppBase/IOkCancelView.h"
#include "../../CrystalViewer/AppBase/Sphere3dView.h"

namespace Crystal {
	namespace Physics {
		class KFFluidScene;
	}
	namespace UI {

class VDBParticleSystemView : public IOkCancelView
{
public:
	VDBParticleSystemView(const std::string& name, Scene::World* model, Canvas* canvas);

private:
	void onOk() override;

private:
	Sphere3dView sphereView;
	DoubleView divideLengthView;
};

	}
}