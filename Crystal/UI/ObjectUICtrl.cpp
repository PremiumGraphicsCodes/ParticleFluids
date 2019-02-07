#include "ObjectUICtrl.h"

using namespace Crystal::Math;
using namespace Crystal::UI;

ObjectUICtrl::ObjectUICtrl()
{
}

void ObjectUICtrl::onLeftButtonDown(const Vector2df& position)
{
	prevPosition = position;
	//	camera->move();
}

void ObjectUICtrl::onLeftButtonUp(const Vector2df& position)
{

}

void ObjectUICtrl::onLeftDragging(const Vector2df& position)
{
	const auto diff = prevPosition - position;
	//camera->move(glm::vec3(diff.x, diff.y, 0.0));
	this->prevPosition = position;
}

void ObjectUICtrl::onRightButtonDown(const Vector2df& position)
{
	prevPosition = position;
}

void ObjectUICtrl::onRightButtonUp(const Vector2df& position)
{

}

void ObjectUICtrl::onRightDragging(const Vector2df& position)
{
	const auto diff = prevPosition - position;
	//camera->rotate(diff.y, diff.x);
	this->prevPosition = position;
}

void ObjectUICtrl::onWheel(const float dx)
{
	//camera->zoom(dx / 100.0f);
}
