#pragma once

#include "IPSAddView.h"

#include "Torus3dView.h"
#include "IntView.h"

namespace Crystal {
	namespace UI {

class PSTorusView : public IPSAddView
{
public:
	PSTorusView(Scene::World* model, Canvas* canvas);

private:
	void onOk() override;

private:
	TorusView torusView;
	IntView count;
};

	}
}