#pragma once

#include "IWindow.h"
#include "ParticleSystemView.h"
#include "IntView.h"
#include "StringView.h"
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
	ParticleSystemView particleSystem;
	Scene::World* world;
	IntView id;
	StringView name;
	Button edit;
};

	}
}
