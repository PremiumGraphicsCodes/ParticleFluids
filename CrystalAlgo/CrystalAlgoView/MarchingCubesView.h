#pragma once

#include "../../CrystalViewer/AppBase/IOkCancelView.h"
#include "../../CrystalViewer/AppBase/ObjectSelectView.h"
#include "../../CrystalViewer/AppBase/DoubleView.h"

namespace Crystal {
	namespace UI {

class MarchingCubesView : public IOkCancelView
{
public:
	MarchingCubesView(Scene::World* model, Canvas* canvas);

	void onShow() override;

	void onOk() override;

private:
	std::array< DoubleView, 8 > values;
};

	}
}