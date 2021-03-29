#pragma once

#include "../../CrystalViewer/AppBase/IOkCancelView.h"
#include "../../CrystalViewer/AppBase/ObjectSelectView.h"
#include "../../CrystalViewer/AppBase/DoubleView.h"

namespace Crystal {
	namespace UI {

class IntersectionView : public IOkCancelView
{
public:
	IntersectionView(Scene::World* model, Canvas* canvas);

private:
	void onShow() override;

	void onOk() override;

private:
	ObjectSelectView mesh1;
	ObjectSelectView mesh2;
	DoubleView tolerance;
};

	}
}