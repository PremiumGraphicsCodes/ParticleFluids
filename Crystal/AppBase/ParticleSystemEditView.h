#pragma once

#include "IWindow.h"
#include "ParticleSystemView.h"
#include "IntView.h"
#include "StringView.h"
#include "../Scene/ParticleSystemScene.h"
#include "../UI/Repository.h"
#include "../UI/Canvas.h"

namespace Crystal {
	namespace UI {

class ParticleSystemEditView : public IWindow
{
public:
	ParticleSystemEditView(const std::string& name, Repository* repository, Canvas* canvas);

	void show() override;

	void setValue(Scene::ParticleSystemScene* value);

private:
	ParticleSystemView particleSystem;
	IntView id;
	StringView name;
};

	}
}
