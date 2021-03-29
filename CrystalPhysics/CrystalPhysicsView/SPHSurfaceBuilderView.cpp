#include "SPHSurfaceBuilderView.h"

using namespace Crystal::Math;
using namespace Crystal::UI;
using namespace Crystal::Scene;

SPHSurfaceBuilderView::SPHSurfaceBuilderView(const std::string& name, World* model, Canvas* canvas) :
	IOkCancelView(name, model, canvas),
	searchRadiusView("SearchRadius")
{
	add(&searchRadiusView);
}

void SPHSurfaceBuilderView::onOk()
{

}