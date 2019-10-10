#pragma once

#include "IWindow.h"
#include "imgui.h"

#include "IntView.h"
#include "../Scene/ParticleSystemScene.h"

namespace Crystal {
	namespace UI {

class ParticleSystemView : public IWindow
{
public:
	explicit ParticleSystemView(const std::string& name);

	void onShow() override;

	void setValue(Scene::ParticleSystemScene* value);

private:
	IntView particleCount;
};

	}
}