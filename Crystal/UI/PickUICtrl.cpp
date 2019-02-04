#include "PickUICtrl.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::UI;

PickUICtrl::PickUICtrl(Repository* model, Canvas* canvas) :
	model(model),
	canvas(canvas)
{
}

void PickUICtrl::onLeftButtonDown(const Vector2df& position)
{
	const auto x = position.x / (double)canvas->getWidth();
	const auto y = position.y / (double)canvas->getHeight();

	//canvas->getRenderer()->get
	
	prevPosition = position;
	//	camera->move();
}

void PickUICtrl::onLeftButtonUp(const Vector2df& position)
{

}

void PickUICtrl::onLeftDragging(const Vector2df& position)
{
	const auto diff = prevPosition - position;
	this->prevPosition = position;
}

void PickUICtrl::onRightButtonDown(const Vector2df& position)
{
	prevPosition = position;
}

void PickUICtrl::onRightButtonUp(const Vector2df& position)
{

}

void PickUICtrl::onRightDragging(const Vector2df& position)
{
	const auto diff = prevPosition - position;
	this->prevPosition = position;
}

void PickUICtrl::onWheel(const float dx)
{
	//camera->zoom(dx);
}
