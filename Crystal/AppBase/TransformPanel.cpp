#include "TransformPanel.h"
#include "MoveButton.h"
#include "ScaleButton.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::UI;

TransformPanel::TransformPanel(const std::string& name, Repository* model, Canvas* canvas) :
	IPanel(name, model, canvas)
{
	add(new MoveButton("Move", model, canvas));
	add(new ScaleButton("Scale", model, canvas));
}
