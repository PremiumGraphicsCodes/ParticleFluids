#pragma once

#include "IPanel.h"
#include "Sphere3dView.h"
#include "PSAttributeView.h"
#include "IntView.h"
#include "Button.h"

namespace Crystal {
	namespace UI {

class PSSphereView : public IPanel
{
public:
	PSSphereView(Repository* model, Canvas* canvas);

	void show() override;

private:
	void onOk();

private:
	Sphere3dView sphere;
	PSAttributeView attribute;
	IntView count;
	Button ok;
};

	}
}