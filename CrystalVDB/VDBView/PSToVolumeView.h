#pragma once

#include "../../CrystalViewer/AppBase/IOkCancelView.h"
#include "../../CrystalViewer/AppBase/ObjectSelectView.h"
#include "../../CrystalViewer/AppBase/Box3dView.h"
#include "../../CrystalViewer/AppBase/DoubleView.h"
#include "../../CrystalViewer/AppBase/DirectoryView.h"

#include "../../CrystalAlgo/CrystalPhysics/KFFluidSolver.h"
#include "TimeSeriesParticleSystemWriter.h"

namespace Crystal {
	namespace Physics {
		class KFFluidScene;
	}
	namespace UI {

class PSToVolumeView : public IOkCancelView
{
public:
	PSToVolumeView(const std::string& name, Scene::World* model, Canvas* canvas);

private:
	void onOk() override;

private:
	ObjectSelectView particleSystemSelectView;
};

	}
}