#pragma once

#include "../../Crystal/AppBase/IOkCancelView.h"
#include "../../Crystal/AppBase/ObjectSelectView.h"
#include "../../Crystal/AppBase/DoubleView.h"

namespace Crystal {
	namespace UI {

class MarchingCubesView : public IOkCancelView
{
public:
	MarchingCubesView(Scene::RootScene* model, Canvas* canvas);

	void show() override;

	void onOk() override;

private:
	std::array< DoubleView, 8 > values;
};

	}
}