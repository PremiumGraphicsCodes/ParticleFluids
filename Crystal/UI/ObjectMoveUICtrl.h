#pragma once

#include <memory>
#include "IUICtrl.h"

namespace Crystal {
	namespace UI {
		class Repository;
		class Canvas;

class ObjectMoveUICtrl : public IUICtrl
{
public:
	ObjectMoveUICtrl(Repository* repository, Canvas* canvas);

	virtual ~ObjectMoveUICtrl() {}

	virtual void onLeftButtonDown(const Math::Vector2df& position) override;

	virtual void onLeftButtonUp(const Math::Vector2df& position) override;

	virtual void onLeftDragging(const Math::Vector2df& position) override;

	virtual void onRightButtonDown(const Math::Vector2df& position) override;

	virtual void onRightButtonUp(const Math::Vector2df& position) override;

	virtual void onRightDragging(const Math::Vector2df& position) override;

	virtual void onWheel(const float dx) override;

private:
	Repository* repository;
	Canvas* canvas;
	Math::Vector2df prevPosition;
};

	}
}