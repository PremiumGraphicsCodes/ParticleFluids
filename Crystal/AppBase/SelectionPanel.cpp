#include "SelectionPanel.h"
#include "ObjectSelectButton.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::UI;


SelectionPanel::SelectionPanel(const std::string& name, Repository* model, Canvas* canvas) :
	IPanel(name, model, canvas)
{
	add(new ObjectSelectButton("Object", model, canvas));
}
