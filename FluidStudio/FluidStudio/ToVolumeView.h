#pragma once

#include "CrystalScene/AppBase/IOkCancelView.h"
#include "CrystalScene/AppBase/DoubleView.h"
#include "CrystalScene/AppBase/DirectoryView.h"

namespace PG {
	namespace FS {

class ToVolumeView : public Crystal::UI::IOkCancelView
{
public:
	ToVolumeView(const std::string& name, Crystal::Scene::World* model, Crystal::UI::Canvas* canvas);

private:
	void onOk() override;

private:
	Crystal::UI::DoubleView particleRadiusView;
	Crystal::UI::DoubleView gridCellWidthView;
	Crystal::UI::DirectoryView inputDirectoryView;
	Crystal::UI::DirectoryView outputDirectoryView;
};

	}
}