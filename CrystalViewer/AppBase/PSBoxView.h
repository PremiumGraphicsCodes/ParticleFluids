#pragma once

#include "IPSAddView.h"

#include "Box3dView.h"
#include "IntView.h"
#include "BoolView.h"

namespace Crystal {
	namespace UI {

class PSBoxView : public IPSAddView
{
public:
	PSBoxView(Scene::World* model, Canvas* canvas);

private:
	void onOk() override;

private:
	Box3dView box;
	IntView count;
	BoolView isVolume;
};

	}
}