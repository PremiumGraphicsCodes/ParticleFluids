#include "TransformPanel.h"
#include "TransformButton.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::UI;

TransformPanel::TransformPanel(const std::string& name, Repository* model, Canvas* canvas) :
	IPanel(name, model, canvas)
{
	add(new TransformButton("Move", model, canvas));
}
