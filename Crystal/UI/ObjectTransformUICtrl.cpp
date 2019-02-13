#include "ObjectTransformUICtrl.h"

#include "Repository.h"

#include "../UI/Canvas.h"

using namespace Crystal::Math;
using namespace Crystal::UI;

ObjectTransformUICtrl::ObjectTransformUICtrl(Repository* repository, Canvas* canvas) :
	repository(repository),
	canvas(canvas)
{
}

void ObjectTransformUICtrl::onLeftButtonDown(const Vector2df& position)
{
	prevPosition = position;
	//	camera->move();
}

void ObjectTransformUICtrl::onLeftButtonUp(const Vector2df& position)
{

}

void ObjectTransformUICtrl::onLeftDragging(const Vector2df& position)
{
	const auto diff = prevPosition - position;

	auto& os = repository->getObjects()->getParticleSystems()->getObjects();
	for (auto& o : os) {
		o.move(glm::vec3(diff.x, diff.y, 0.0));
	}
	this->prevPosition = position;
	canvas->setViewModel(repository->toViewModel());
}

void ObjectTransformUICtrl::onRightButtonDown(const Vector2df& position)
{
	prevPosition = position;
}

void ObjectTransformUICtrl::onRightButtonUp(const Vector2df& position)
{

}

void ObjectTransformUICtrl::onRightDragging(const Vector2df& position)
{
	const auto& diff = prevPosition - position;
	const auto& rotation = rotationMatrixX(diff.x) * rotationMatrixY(diff.y);

	auto& os = repository->getObjects()->getParticleSystems()->getObjects();
	for (auto& o : os) {
		o.transform(rotation);
	}
	this->prevPosition = position;
	canvas->setViewModel(repository->toViewModel());
}

void ObjectTransformUICtrl::onMiddleButtonDown(const Vector2df& position)
{

}

void ObjectTransformUICtrl::onMiddleButtonUp(const Vector2df& position)
{

}

void ObjectTransformUICtrl::onMiddleDragging(const Vector2df& position)
{

}


void ObjectTransformUICtrl::onWheel(const float dx)
{
	//camera->zoom(dx / 100.0f);
}
