#include "PickUICtrl.h"

#include "../UI/Repository.h"

#include <iostream>

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::UI;

PickUICtrl::PickUICtrl(Repository* model, Canvas* canvas) :
	model(model),
	canvas(canvas)
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

	const auto id = canvas->getRenderer()->getObjectIdRenderer()->getId(x, y);
	const auto parentId = id.getParentId();
	const auto childId = id.getChildId();
	if (parentId == 0) {
		return;
	}
	auto object = model->getObjects()->findObjectById(parentId);
	if (object != nullptr) {
		function(parentId, childId);
		/*
		auto selected = model->getObjects()->getParticleSystems()->findParticleById(parentId, childId);
		if (selected != nullptr) {
			const auto size = selected->getAttribute().size * 100.0;
			model->getItems()->getParticleSystems()->addObject(selected->getPosition(), Graphics::ColorRGBAf(1, 0, 0, 1), size, "");
			canvas->setViewModel(model->toViewModel());
		}
		*/
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
