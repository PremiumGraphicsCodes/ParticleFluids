#pragma once

#include "../../Crystal/Scene/ParticleSystemScene.h"
#include "../../Crystal/Scene/World.h"

#include "IEditCancelView.h"
#include "ParticleSystemView.h"
#include "IntView.h"
#include "PSAttributeView.h"
#include "Canvas.h"

#include "ComboBox.h"

namespace Crystal {
	namespace UI {

class ParticleSystemEditView : public IEditCancelView
{
public:
	ParticleSystemEditView(const std::string& name, Scene::World* world, Canvas* canvas);

	void setValue(Scene::ParticleSystemScene* value);

private:
	void onEdit();

private:
	IntView idView;
	ParticleSystemView particleSystemView;
	PSAttributeView attributeView;
	ComboBox presenterView;
};

	}
}
