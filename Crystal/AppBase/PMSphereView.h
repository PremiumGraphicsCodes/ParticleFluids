#pragma once

#include "IPanel.h"
#include "Sphere3dView.h"
#include "IntView.h"
#include "StringView.h"
#include "Button.h"

namespace Crystal {
	namespace UI {

class PMSphereView : public IPanel
{
public:
	PMSphereView(Scene::RootScene* model, Canvas* canvas);

	void show() override;

private:
	void onOk();

private:
	Sphere3dView sphere;
	IntView unum;
	IntView vnum;
	StringView materialName;
	StringView name;
	Button ok;
};

	}
}