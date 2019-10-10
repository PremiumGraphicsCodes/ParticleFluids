#pragma once

#include "IOkCancelView.h"
#include "Sphere3dView.h"
#include "IntView.h"
#include "StringView.h"

namespace Crystal {
	namespace UI {

class PMSphereView : public IOkCancelView
{
public:
	PMSphereView(Scene::World* model, Canvas* canvas);

private:
	void onOk() override;

private:
	Sphere3dView sphere;
	IntView unum;
	IntView vnum;
	StringView name;
};

	}
}