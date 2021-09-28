#pragma once

#include "CrystalScene/AppBase/IOkCancelView.h"
#include "CrystalScene/AppBase/FloatView.h"
#include "CrystalScene/AppBase/ObjectSelectView.h"

namespace Crystal {
	namespace UI {

class VoxelizerCommandView : public IOkCancelView
{
public:
	VoxelizerCommandView(const std::string& name, Scene::World* model, Canvas* canvas);

private:
	void onOk() override;

private:
	FloatView divideLengthView;
};

	}
}