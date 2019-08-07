#pragma once

#include "IOkCancelView.h"
#include "Sphere3dView.h"
#include "PSAttributeView.h"
#include "IntView.h"

namespace Crystal {
	namespace UI {

class PSSphereView : public IOkCancelView
{
public:
	PSSphereView(Scene::World* model, Canvas* canvas);

	void show() override;

private:
	void onOk() override;

private:
	Sphere3dView sphere;
	PSAttributeView attribute;
	IntView count;
};

	}
}