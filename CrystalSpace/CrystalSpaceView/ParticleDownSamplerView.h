#pragma once

#include "CrystalScene/AppBase/IOkCancelView.h"

namespace Crystal {
	namespace UI {

class ParticleDownSamplerView : public IOkCancelView
{
public:
	ParticleDownSamplerView(const std::string& name, Scene::World* model, Canvas* canvas);

private:
	void onOk() override;

};

	}
}