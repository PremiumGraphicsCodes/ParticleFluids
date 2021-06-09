#pragma once

#include "../../CrystalViewer/AppBase/IOkCancelView.h"
#include "../../CrystalViewer/AppBase/StringView.h"
#include "../../CrystalViewer/AppBase/ComboBox.h"
#include "../../CrystalViewer/AppBase/ColorMapView.h"
#include "../CrystalSpace/SparseVolume.h"

namespace Crystal {
	namespace UI {

class ISVAddView : public IOkCancelView
{
public:
	ISVAddView(const std::string& name, Scene::World* model, Canvas* canvas);

protected:
	void addVolume(std::unique_ptr<Space::SparseVolumed> volume);

private:
	StringView nameView;
	ComboBox presenterView;
	ColorMapView colorMapView;
};

	}
}