#pragma once

#include "../../CrystalViewer/AppBase/IOkCancelView.h"
#include "../../CrystalViewer/AppBase/ObjectSelectView.h"
//#include "../../CrystalViewer/AppBase/FileOpenView.h"

namespace Crystal {
	namespace Physics {
		class KFFluidScene;
	}
	namespace UI {

class OBJFileExportView : public IOkCancelView
{
public:
	OBJFileExportView(const std::string& name, Scene::World* model, Canvas* canvas);

private:
	void onOk() override;

	ObjectSelectView vdbMeshSelectView;
	//FilePathView filePathView;
};

	}
}