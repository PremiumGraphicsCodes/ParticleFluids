#pragma once

#include "../../CrystalViewer/AppBase/IOkCancelView.h"
#include "../../CrystalViewer/AppBase/ObjectSelectView.h"

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
	ObjectSelectView particleSystemSelectView;
};

	}
}