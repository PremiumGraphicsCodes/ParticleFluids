#include "TransformPanel.h"

using namespace Crystal::Math;
using namespace Crystal::UI;

TransformPanel::TransformPanel(const std::string& name, Repository* model, Canvas* canvas) :
	IPanel(name, model, canvas),
	translate("Translate")
{
}
