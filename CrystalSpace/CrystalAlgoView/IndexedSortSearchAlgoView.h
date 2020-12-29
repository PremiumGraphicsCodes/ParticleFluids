#pragma once

#include "../../CrystalViewer/AppBase/IOkCancelView.h"
#include "../../CrystalViewer/AppBase/DoubleView.h"

namespace Crystal {
	namespace UI {

class IndexedSortSearchAlgoView : public IOkCancelView
{
public:
	IndexedSortSearchAlgoView(Scene::World* model, Canvas* canvas);

private:
	void onOk() override;

private:
	DoubleView searchRadius;
};

	}
}