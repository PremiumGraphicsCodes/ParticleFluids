#pragma once

#include "../../CrystalViewer/AppBase/IOkCancelView.h"
#include "../../CrystalViewer/AppBase/ObjectSelectView.h"

namespace Crystal {
	namespace UI {

class VolumeToPSView : public IOkCancelView
{
public:
	VolumeToPSView(const std::string& name, Scene::World* model, Canvas* canvas);

private:
	void onOk() override;

private:
	ObjectSelectView vdbVolumeSelectView;
};

	}
}