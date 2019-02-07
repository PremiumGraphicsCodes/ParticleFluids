#pragma once

#include <memory>
#include "IUICtrl.h"

namespace Crystal {
	namespace UI {
		class ObjectRepository;

class ObjectUICtrl : public IUICtrl
{
public:
	ObjectUICtrl(ObjectRepository* objects);

	virtual ~ObjectUICtrl() {}

	virtual void onLeftButtonDown(const Math::Vector2df& position) override;

	virtual void onLeftButtonUp(const Math::Vector2df& position) override;

	virtual void onLeftDragging(const Math::Vector2df& position) override;

	virtual void onRightButtonDown(const Math::Vector2df& position) override;

	virtual void onRightButtonUp(const Math::Vector2df& position) override;

	virtual void onRightDragging(const Math::Vector2df& position) override;

	virtual void onWheel(const float dx) override;

private:
	ObjectRepository* objects;
	Math::Vector2df prevPosition;
};

	}
}