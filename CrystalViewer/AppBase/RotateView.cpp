#include "RotateView.h"
#include "../../Crystal/Scene/IShapeScene.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::UI;

RotateView::RotateView(const std::string& name, World* scene, Canvas* canvas) :
	IOkCancelView(name, scene, canvas),
	objectSelectView("Object", model, canvas),
	matrixView("Matrix")
{
	add(&objectSelectView);
	add(&matrixView);
}

void RotateView::onOk()
{
	auto shape = model->getObjects()->findSceneById<IShapeScene*>( objectSelectView.getId() );
	if (shape == nullptr) {
		return;
	}
	const auto& matrix = matrixView.getValue();
	shape->transform(matrix);
	//model->updateViewModel();
}