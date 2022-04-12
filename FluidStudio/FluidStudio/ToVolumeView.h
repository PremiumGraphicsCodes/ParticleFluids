#pragma once

#include "CrystalScene/AppBase/IOkCancelView.h"
#include "CrystalScene/AppBase/DoubleView.h"
#include "CrystalScene/AppBase/DirectoryView.h"

namespace Crystal {
	namespace UI {

class ToVolumeView : public IOkCancelView
{
public:
	ToVolumeView(const std::string& name, Scene::World* model, Canvas* canvas);

private:
	void onOk() override;

private:
	DoubleView particleRadiusView;
	DoubleView gridCellWidthView;
	DirectoryView inputDirectoryView;
	DirectoryView outputDirectoryView;
};

	}
}