#pragma once

#include "ObjectSelectButton.h"
#include "Sphere3dView.h"

namespace Crystal {
	namespace UI {

class SphereRegionSelectButton : public IPopupButton
{
public:
	SphereRegionSelectButton(const std::string& name, Repository* model, Canvas* canvas) :
		IPopupButton(name, model, canvas),
		object("Object", model, canvas, Model::SceneType::ParticleSystemObject),
		sphere("Region")
	{
	}

	void onShow() override;

	void onOk() override;

	void onCancel() override;

	//std::vector<Math::Vector3dd> getSelected() const { return positions; }

private:
	ObjectSelectButton object;
	Sphere3dView sphere;
};

	}
}