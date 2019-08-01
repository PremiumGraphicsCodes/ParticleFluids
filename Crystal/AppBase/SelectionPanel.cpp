#include "SelectionPanel.h"
#include "ObjectSelectView.h"
#include "PositionSelectView.h"
#include "SphereRegionSelectButton.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::UI;
using namespace Crystal::Scene;

SelectionPanel::SelectionPanel(const std::string& name, RootScene* model, Canvas* canvas) :
	IPanel(name, model, canvas)
{
	add(new ObjectSelectView("Shape", model, canvas));
	add(new PositionSelectView("Position", model, canvas));
	add(new SphereRegionSelectButton("SphereRegion", model, canvas));
}
