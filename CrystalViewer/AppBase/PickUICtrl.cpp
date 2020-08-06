#include "PickUICtrl.h"

#include "../../Crystal/Scene/World.h"
#include "../Command/Command.h"
#include "../Command/Public/PickLabels.h"

#include <iostream>

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Scene;
using namespace Crystal::UI;

PickUICtrl::PickUICtrl(World* model, Canvas* canvas, const SceneType& type) :
	model(model),
	canvas(canvas),
	type(type)
{
	function = [](int parentId, int childId) {
		;
	};
}

void PickUICtrl::onLeftButtonDown(const Vector2df& position)
{
	const auto x = position.x;
	const auto y = position.y;

	std::cout << x << " " << y << std::endl;

	Crystal::Command::Command command(PickLabels::PickCommandLabel);
	command.setArg(PickLabels::PositionLabel, Vector2dd(position));
	command.execute(model);
	const auto parentId = std::any_cast<int>( command.getResult(PickLabels::ParentIdLabel) );
	const auto childId = std::any_cast<int>(command.getResult(PickLabels::ChildIdLabel));

	auto object = model->getScenes()->findSceneById(parentId);
	if (object != nullptr) {
		const bool masked = (int)type && (int)object->getType();
		if (masked) {
			function(parentId, childId);
		}
	}
}

void PickUICtrl::onLeftButtonUp(const Vector2df& position)
{

}

void PickUICtrl::onLeftDragging(const Vector2df& position)
{
}

void PickUICtrl::onRightButtonDown(const Vector2df& position)
{
}

void PickUICtrl::onRightButtonUp(const Vector2df& position)
{

}

void PickUICtrl::onRightDragging(const Vector2df& position)
{
}

void PickUICtrl::onWheel(const float dx)
{
	//camera->zoom(dx);
}
