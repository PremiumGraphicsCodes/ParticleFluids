#pragma once

#include "../../CrystalViewer/AppBase/IOkCancelView.h"
#include "../../CrystalViewer/AppBase/DoubleView.h"
#include "../../CrystalViewer/AppBase/ObjectSelectView.h"

namespace Crystal {
	namespace UI {

class VoxelizerView : public IOkCancelView
{
public:
	VoxelizerView(const std::string& name, Scene::World* model, Canvas* canvas);

private:
	void toPoints();

	void toVolume();

	void onOk() override;

private:
	Button toPointsButton;
	Button toVoxelButton;
	DoubleView divideLengthView;
};

	}
}