#include "TransformPanel.h"
#include "ObjectMoveButton.h"
#include "ObjectScaleButton.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::UI;

TransformPanel::TransformPanel(const std::string& name, Repository* model, Canvas* canvas) :
	IPanel(name, model, canvas)
{
	add(new ObjectMoveButton("Move", model, canvas));
	add(new ObjectScaleButton("Scale", model, canvas));
}
