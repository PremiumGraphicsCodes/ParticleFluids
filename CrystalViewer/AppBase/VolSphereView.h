#pragma once

#include "IVolAddView.h"

namespace Crystal {
	namespace UI {

class VolSphereView : public IVolAddView
{
public:
	VolSphereView(const std::string& name, Scene::World* world, Canvas* canvas);

	void onOk() override;

};

	}
}