#pragma once

#include "../../CrystalViewer/AppBase/IView.h"
#include "../../CrystalViewer/AppBase/Box3dView.h"
#include "../../CrystalViewer/AppBase/Button.h"
#include "../CrystalPhysics/CSGBoundaryScene.h"

namespace Crystal {
	namespace Scene {
		class World;
	}
	namespace UI {

class CSGBoundaryView : public IView
{
public:
	explicit CSGBoundaryView(const std::string& name, Scene::World* model);

	Physics::CSGBoundaryScene* getBoundary() const { return boundary.get(); }

private:
	void onApply();

	Box3dView boxView;
	Button applyButton;	
	std::unique_ptr<Physics::CSGBoundaryScene> boundary;
};

	}
}