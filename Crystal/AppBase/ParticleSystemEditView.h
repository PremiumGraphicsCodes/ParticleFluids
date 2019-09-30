#pragma once

#include "IWindow.h"
#include "ParticleSystemView.h"
#include "IntView.h"
#include "PSAttributeView.h"
#include "Button.h"
#include "../Scene/ParticleSystemScene.h"
#include "../Scene/World.h"
#include "Canvas.h"

namespace Crystal {
	namespace UI {

class ParticleSystemEditView : public IWindow
{
public:
	ParticleSystemEditView(const std::string& name, Scene::World* repository, Canvas* canvas);

	void onShow() override;

	void setValue(Scene::ParticleSystemScene* value);

private:
	void onEdit();

private:
	ParticleSystemView particleSystemView;
	Scene::World* world;
	Canvas* canvas;
	IntView idView;
	PSAttributeView attributeView;
	Button edit;
};

	}
}
