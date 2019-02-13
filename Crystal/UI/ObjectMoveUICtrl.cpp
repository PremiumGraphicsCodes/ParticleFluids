#include "ObjectMoveUICtrl.h"

#include "Repository.h"

#include "../UI/Canvas.h"

using namespace Crystal::Math;
using namespace Crystal::UI;

ObjectMoveUICtrl::ObjectMoveUICtrl(Repository* repository, Canvas* canvas) :
	repository(repository),
	canvas(canvas)
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

	auto& os = repository->getObjects()->getParticleSystems()->getObjects();
	for (auto& o : os) {
		o.move(glm::vec3(diff.x, diff.y, 0.0));
	}
	this->prevPosition = position;
	canvas->setViewModel(repository->toViewModel());
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
