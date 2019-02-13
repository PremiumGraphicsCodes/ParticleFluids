#include "TransformUICtrl.h"

#include "Repository.h"

#include "../UI/Canvas.h"

using namespace Crystal::Math;
using namespace Crystal::UI;

TransformUICtrl::TransformUICtrl(Repository* repository, Canvas* canvas) :
	repository(repository),
	canvas(canvas)
{
}

void TransformUICtrl::onLeftButtonDown(const Vector2df& position)
{
	prevPosition = position;
	//	camera->move();
}

void TransformUICtrl::onLeftButtonUp(const Vector2df& position)
{

}

void TransformUICtrl::onLeftDragging(const Vector2df& position)
{
	const auto diff = prevPosition - position;

	auto& os = repository->getObjects()->getParticleSystems()->getObjects();
	for (auto& o : os) {
		o.move(glm::vec3(diff.x, diff.y, 0.0));
	}
	this->prevPosition = position;
	canvas->setViewModel(repository->toViewModel());
}

void TransformUICtrl::onRightButtonDown(const Vector2df& position)
{
	prevPosition = position;
}

void TransformUICtrl::onRightButtonUp(const Vector2df& position)
{

}

void TransformUICtrl::onRightDragging(const Vector2df& position)
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

void TransformUICtrl::onMiddleButtonDown(const Vector2df& position)
{

}

void TransformUICtrl::onMiddleButtonUp(const Vector2df& position)
{

}

void TransformUICtrl::onMiddleDragging(const Vector2df& position)
{

}


void TransformUICtrl::onWheel(const float dx)
{
	//camera->zoom(dx / 100.0f);
}
