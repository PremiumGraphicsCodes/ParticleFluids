#pragma once

#include "IOkCancelView.h"

#include "Box3dView.h"
#include "PSAttributeView.h"
#include "IntView.h"
#include "BoolView.h"

namespace Crystal {
	namespace UI {

class PSBoxView : public IOkCancelView
{
public:
	PSBoxView(Scene::World* model, Canvas* canvas);

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