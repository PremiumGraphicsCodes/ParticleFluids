#pragma once

//#include "IWFAddView.h"
#include "Box3dView.h"

namespace Crystal {
	namespace UI {

class SolidBoxView : public IWFAddView
{
public:
	SolidBoxView(const std::string& name, Scene::World* world, Canvas* canvas);

private:
	void onOk() override;

private:
	Box3dView boxView;
};

	}
}

