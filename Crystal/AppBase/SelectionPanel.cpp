#include "SelectionPanel.h"
#include "ObjectSelectButton.h"
#include "PositionSelectButton.h"
#include "SphereRegionSelectButton.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::UI;
using namespace Crystal::Scene;

SelectionPanel::SelectionPanel(const std::string& name, RootScene* model, Canvas* canvas) :
	IPanel(name, model, canvas)
{
	add(new ObjectSelectButton("Shape", model, canvas));
	add(new PositionSelectButton("Position", model, canvas));
	add(new SphereRegionSelectButton("SphereRegion", model, canvas));
}
