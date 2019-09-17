#include "TransformView.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::UI;

TransformView::TransformView(const std::string& name, World* model, Canvas* canvas) :
	IOkCancelView(name, model, canvas),
	objectSelectView("Object", model, canvas),
	matrixView("Matrix", Matrix4dd())
{
	add(&objectSelectView);
	add(&matrixView);
}

void TransformView::onOk()
{
	;
}
