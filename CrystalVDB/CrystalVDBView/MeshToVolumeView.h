#pragma once

#include "../../CrystalViewer/AppBase/IOkCancelView.h"
#include "../../CrystalViewer/AppBase/ObjectSelectView.h"
#include "../../CrystalViewer/AppBase/Box3dView.h"
#include "../../CrystalViewer/AppBase/DoubleView.h"
#include "../../CrystalViewer/AppBase/MaterialSelectView.h"

namespace Crystal {
	namespace UI {

class MeshToVolumeView : public IOkCancelView
{
public:
	MeshToVolumeView(const std::string& name, Scene::World* model, Canvas* canvas);

private:
	void onOk() override;

private:
	ObjectSelectView vdbMeshSelectView;
	DoubleView divideLengthView;
};

	}
}