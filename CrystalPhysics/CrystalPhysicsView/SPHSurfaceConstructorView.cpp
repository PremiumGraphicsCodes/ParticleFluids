#include "SPHSurfaceConstructorView.h"

using namespace Crystal::Math;
using namespace Crystal::UI;
using namespace Crystal::Scene;

SPHSurfaceConstructorView::SPHSurfaceConstructorView(const std::string& name, World* model, Canvas* canvas) :
	IOkCancelView(name, model, canvas),
	searchRadiusView("SearchRadius")
{
	add(&searchRadiusView);
}

void SPHSurfaceConstructorView::onOk()
{

}