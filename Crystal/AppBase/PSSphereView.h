#pragma once

#include "IPSAddView.h"
#include "Sphere3dView.h"
#include "PSAttributeView.h"
#include "IntView.h"

namespace Crystal {
	namespace UI {

class PSSphereView : public IPSAddView
{
public:
	PSSphereView(Scene::World* model, Canvas* canvas);

private:
	void onOk() override;

private:
	Sphere3dView sphere;
	IntView count;
};

	}
}