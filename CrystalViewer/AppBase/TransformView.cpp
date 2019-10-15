#include "TransformView.h"

#include "../../Crystal/Scene/IShapeScene.h"
#include "../Command/Command.h"
//#include "../Command/Public/"

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
	Crystal::Command::Command command("Transform");
	command.setArg("Id", objectSelectView.getId());
	command.setArg("Matrix", matrixView.getValue());
	command.execute(getWorld());
	/*
	const auto id = objectSelectView.getId();
	auto scene = getWorld()->getObjects()->findSceneById<IShapeScene*>(id);
	const auto& matrix = matrixView.getValue();
	scene->transform(matrix);
	*/
	getWorld()->updateViewModel();
}
