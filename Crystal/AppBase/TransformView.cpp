#include "TransformView.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::UI;

TransformView::TransformView(const std::string& name, World* model, Canvas* canvas) :
	IPanel(name, model, canvas),
	translate("Translate"),
	rotation("Rotation")
{
}

void TransformView::onShow()
{
	translate.show();
	rotation.show();
}

