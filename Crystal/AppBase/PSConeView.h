#pragma once

#include "IPSAddView.h"

#include "Cone3dView.h"
#include "IntView.h"
#include "StringView.h"

namespace Crystal {
	namespace UI {

class PSConeView : public IPSAddView
{
public:
	PSConeView(Scene::World* model, Canvas* canvas);

private:
	void onOk() override;

private:
	Cone3dView cone;
	IntView count;
};

	}
}
