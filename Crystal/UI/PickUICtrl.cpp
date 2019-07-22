#include "PickUICtrl.h"

#include "../UI/Repository.h"

#include <iostream>

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Scene;
using namespace Crystal::UI;

PickUICtrl::PickUICtrl(Repository* model, Canvas* canvas, const SceneType& type) :
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
	
	auto tex = model->getObjects()->findSceneByName<TextureScene*>("IdTexture");
	const auto id = canvas->getRenderer()->getObjectIdRenderer()->getId(x, y, *tex->getTexture());
	const auto parentId = id.getParentId();
	const auto childId = id.getChildId();
	if (parentId == 0) {
		return;
	}
	auto object = model->getObjects()->findSceneById(parentId);
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
