#pragma once

#include "../../CrystalViewer/AppBase/IOkCancelView.h"
#include "../../CrystalViewer/AppBase/DoubleView.h"
#include "../../CrystalViewer/AppBase/ObjectSelectView.h"

namespace Crystal {
	namespace UI {

class MeshToVoxelView : public IOkCancelView
{
public:
	MeshToVoxelView(const std::string& name, Scene::World* model, Canvas* canvas);

private:
	void onOk() override;

private:
	//ObjectSelectView polygonMeshSelectView;
	DoubleView divideLengthView;
};

	}
}