#pragma once

#include <list>
#include "IUICtrl.h"

namespace Crystal {
	namespace Scene {
		class IScene;
	}
	namespace UI {
		class RootScene;
		class Canvas;


class RotateUICtrl : public IUICtrl
{
public:
	RotateUICtrl(RootScene* repository, Canvas* canvas);

	void add(Scene::IScene* object) { objects.push_back(object); }

	virtual ~RotateUICtrl() {}

	virtual void onLeftButtonDown(const Math::Vector2df& position) override;

	virtual void onLeftButtonUp(const Math::Vector2df& position) override;

	virtual void onLeftDragging(const Math::Vector2df& position) override;

	virtual void onRightButtonDown(const Math::Vector2df& position) override;

	virtual void onRightButtonUp(const Math::Vector2df& position) override;

	virtual void onRightDragging(const Math::Vector2df& position) override {}

	virtual void onMiddleButtonDown(const Math::Vector2df& position) override {}

	virtual void onMiddleButtonUp(const Math::Vector2df& position) override {}

	virtual void onMiddleDragging(const Math::Vector2df& position) override {}

	virtual void onWheel(const float dx) override {}

private:
	std::list<Scene::IScene*> objects;
	RootScene* repository;
	Canvas* canvas;
	Math::Vector2df prevPosition;
};

	}
}