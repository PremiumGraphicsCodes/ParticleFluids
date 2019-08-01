#include "TransformView.h"

using namespace Crystal::Math;
using namespace Crystal::UI;

TransformView::TransformView(const std::string& name, RootScene* model, Canvas* canvas) :
	IPanel(name, model, canvas),
	translate("Translate"),
	rotation("Rotation")
{
}

void TransformView::show()
{
	translate.show();
	rotation.show();
}

