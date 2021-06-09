#pragma once

#include "IVoxelAddView.h"
#include "../../CrystalViewer/AppBase/Sphere3dView.h"
#include "../../CrystalViewer/AppBase/IntView.h"

namespace Crystal {
	namespace UI {

class VoxelSphereView : public IVoxelAddView
{
public:
	VoxelSphereView(const std::string& name, Scene::World* world, Canvas* canvas);

	void onOk() override;

private:
	Sphere3dView sphereView;
	IntView resolutionView;
};

	}
}