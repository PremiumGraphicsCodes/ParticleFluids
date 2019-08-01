#pragma once

#include "IOkCancelView.h"

#include "Box3dView.h"
#include "PSAttributeView.h"
#include "IntView.h"
#include "BoolView.h"
#include "Button.h"

namespace Crystal {
	namespace UI {

class PSBoxView : public IOkCancelView
{
public:
	PSBoxView(Scene::RootScene* model, Canvas* canvas);

	void show() override;

private:
	void onOk() override;

private:
	Box3dView box;
	PSAttributeView attribute;
	IntView count;
	BoolView isVolume;
	StringView name;
};

	}
}