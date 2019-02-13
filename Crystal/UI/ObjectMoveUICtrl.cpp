#include "ObjectMoveUICtrl.h"

#include "ObjectRepository.h"

using namespace Crystal::Math;
using namespace Crystal::UI;

ObjectMoveUICtrl::ObjectMoveUICtrl(ObjectRepository* objects) :
	objects(objects)
{
}

void ObjectMoveUICtrl::onLeftButtonDown(const Vector2df& position)
{
	prevPosition = position;
	//	camera->move();
}

void ObjectMoveUICtrl::onLeftButtonUp(const Vector2df& position)
{

}

void ObjectMoveUICtrl::onLeftDragging(const Vector2df& position)
{
	const auto diff = prevPosition - position;

	const auto& os = objects->getAllObjects();
	for (auto o : os) {
		o->move(glm::vec3(diff.x, diff.y, 0.0));
	}
	this->prevPosition = position;
}

void ObjectMoveUICtrl::onRightButtonDown(const Vector2df& position)
{
	prevPosition = position;
}

void ObjectMoveUICtrl::onRightButtonUp(const Vector2df& position)
{

}

void ObjectMoveUICtrl::onRightDragging(const Vector2df& position)
{
	const auto diff = prevPosition - position;
	//camera->rotate(diff.y, diff.x);
	this->prevPosition = position;
}

void ObjectMoveUICtrl::onWheel(const float dx)
{
	//camera->zoom(dx / 100.0f);
}
