#include "SelectionPanel.h"
#include "ObjectSelectButton.h"
#include "PositionSelectButton.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::UI;


SelectionPanel::SelectionPanel(const std::string& name, Repository* model, Canvas* canvas) :
	IPanel(name, model, canvas)
{
	add(new ObjectSelectButton("Object", model, canvas));
	add(new PositionSelectButton("Position", model, canvas));
}
