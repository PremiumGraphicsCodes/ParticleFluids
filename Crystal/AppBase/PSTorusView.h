#pragma once

#include "IPanel.h"

#include "Torus3dView.h"
#include "PSAttributeView.h"
#include "IntView.h"
#include "Button.h"

namespace Crystal {
	namespace UI {

class PSTorusView : public IPanel
{
public:
	PSTorusView(Scene::RootScene* model, Canvas* canvas);

	void show() override;

	void onOk();

private:
	TorusView torusView;
	PSAttributeView attribute;
	IntView count;
	Button ok;
};

	}
}