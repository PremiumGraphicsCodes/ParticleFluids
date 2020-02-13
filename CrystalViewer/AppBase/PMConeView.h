#pragma once

#include "IOkCancelView.h"

#include "Cone3dView.h"
#include "StringView.h"

namespace Crystal {
	namespace UI {

class PMConeView : public IOkCancelView
{
public:
	PMConeView(const std::string& name, Scene::World* world, Canvas* canvas);

private:
	void onOk() override;

private:
	Cone3dView coneView;
	StringView nameView;
};

	}
}