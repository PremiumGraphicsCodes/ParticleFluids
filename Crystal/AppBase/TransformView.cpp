#include "TransformView.h"

#include "../Scene/IShapeScene.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::UI;

TransformView::TransformView(const std::string& name, World* model, Canvas* canvas) :
	IOkCancelView(name, model, canvas),
	objectSelectView("Object", model, canvas),
	matrixView("Matrix", glm::identity<Matrix4dd>())
{
	add(&objectSelectView);
	add(&matrixView);
}

void TransformView::onOk()
{
	const auto id = objectSelectView.getId();
	auto scene = getWorld()->getObjects()->findSceneById<IShapeScene*>(id);
	const auto& matrix = matrixView.getValue();
	scene->transform(matrix);
	getWorld()->updateViewModel();
}
