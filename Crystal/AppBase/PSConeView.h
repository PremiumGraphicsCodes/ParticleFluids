#pragma once

#include "IOkCancelView.h"

#include "Cone3dView.h"
#include "PSAttributeView.h"
#include "IntView.h"
#include "StringView.h"
#include "IPanel.h"

namespace Crystal {
	namespace UI {

class PSConeView : public IOkCancelView
{
public:
	PSConeView(Scene::World* model, Canvas* canvas);

private:
	void onShow() override;

	void onOk() override;

private:
	Cone3dView cone;
	PSAttributeView attribute;
	IntView count;
	StringView name;
};

	}
}
