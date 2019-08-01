#pragma once

#include "ObjectSelectView.h"
#include "Sphere3dView.h"

namespace Crystal {
	namespace UI {

class SphereRegionSelectView : public IPanel
{
public:
	SphereRegionSelectView(const std::string& name, Scene::RootScene* model, Canvas* canvas) :
		IPanel(name, model, canvas),
		object("Object", model, canvas, Scene::SceneType::ParticleSystemScene),
		sphere("Region")
	{
	}

	void show() override;

	//std::vector<Math::Vector3dd> getSelected() const { return positions; }

private:
	ObjectSelectView object;
	Sphere3dView sphere;
};

	}
}