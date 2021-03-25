#pragma once

#include "../../CrystalViewer/AppBase/IOkCancelView.h"
#include "../../CrystalViewer/AppBase/StringView.h"
#include "../../CrystalViewer/AppBase/ComboBox.h"
#include "../../CrystalViewer/AppBase/ColorMapView.h"
#include "../../Crystal/Shape/Volume.h"

namespace Crystal {
	namespace UI {

class ISparseVolumeAddView : public IOkCancelView
{
public:
	ISparseVolumeAddView(const std::string& name, Scene::World* model, Canvas* canvas);

protected:
	void addVolume(std::unique_ptr<Shape::Volume<float>> volume);

private:
	StringView nameView;
	ComboBox presenterView;
	ColorMapView colorMapView;
};

	}
}