#pragma once

#include "IWindow.h"
#include "ParticleSystemView.h"
#include "IntView.h"
#include "StringView.h"
#include "Button.h"
#include "../Scene/ParticleSystemScene.h"
#include "../Scene/RootScene.h"
#include "../UI/Canvas.h"

namespace Crystal {
	namespace UI {

class ParticleSystemEditView : public IWindow
{
public:
	ParticleSystemEditView(const std::string& name, Scene::RootScene* repository, Canvas* canvas);

	void show() override;

	void setValue(Scene::ParticleSystemScene* value);

private:
	void onEdit();

private:
	ParticleSystemView particleSystem;
	IntView id;
	StringView name;
	Button edit;
};

	}
}
