#pragma once

#include "../../CrystalViewer/AppBase/IOkCancelView.h"
#include "../../CrystalViewer/AppBase/StringView.h"
#include "../CrystalSpace/Voxel.h"

namespace Crystal {
	namespace UI {

class IVoxelAddView : public IOkCancelView
{
public:
	IVoxelAddView(const std::string& name, Scene::World* model, Canvas* canvas);

protected:
	void addVoxel(std::unique_ptr<Space::SparseVoxel> voxel);

private:
	StringView nameView;
};

	}
}