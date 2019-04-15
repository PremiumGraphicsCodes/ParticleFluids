#include "ScaleUICtrl.h"

#include "Repository.h"

#include "../UI/Canvas.h"

using namespace Crystal::Math;
using namespace Crystal::UI;

ScaleUICtrl::ScaleUICtrl(Repository* repository, Canvas* canvas) :
	repository(repository),
	canvas(canvas)
{
}

void ScaleUICtrl::onLeftButtonDown(const Vector2df& position)
{
	prevPosition = position;
}

void ScaleUICtrl::onLeftButtonUp(const Vector2df& position)
{

}

void ScaleUICtrl::onLeftDragging(const Vector2df& position)
{
	const auto diff = prevPosition - position;

	for (auto o : this->objects) {
		//o->(glm::vec3(diff.x, diff.y, 0.0));
	}
	this->prevPosition = position;
	canvas->setViewModel(repository->toViewModel());
}

void ScaleUICtrl::onRightButtonDown(const Vector2df& position)
{
	prevPosition = position;
}

void ScaleUICtrl::onRightButtonUp(const Vector2df& position)
{

}