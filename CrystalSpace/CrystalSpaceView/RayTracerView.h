#pragma once

#include "../../CrystalViewer/AppBase/IOkCancelView.h"
#include "../../CrystalViewer/AppBase/IntView.h"

namespace Crystal {
	namespace UI {

class RayTracerView : public IOkCancelView
{
public:
	RayTracerView(const std::string& name, Scene::World* model, Canvas* canvas);

private:
	void onOk() override;

private:
	IntView maxLevel;
};

	}
}