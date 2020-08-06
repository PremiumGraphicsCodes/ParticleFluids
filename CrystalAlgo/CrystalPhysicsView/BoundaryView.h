#include "../../CrystalViewer/AppBase/IOkCancelView.h"
#include "../../CrystalViewer/AppBase/ObjectSelectView.h"
#include "../../CrystalViewer/AppBase/DoubleView.h"

#include "../CrystalPhysics/KFFluidSolver.h"
#include "../CrystalPhysics/Boundary.h"

namespace Crystal {
	namespace UI {

class BoundaryView : public IOkCancelView
{
public:
	BoundaryView(const std::string& name, Scene::World* model, Canvas* canvas);

	Physics::Boundary getBoundary() const { return boundary; }

private:
	void onOk() override;

private:
	ObjectSelectView meshSelectView;
	DoubleView divideLengthView;
	Physics::Boundary boundary;
};

	}
}