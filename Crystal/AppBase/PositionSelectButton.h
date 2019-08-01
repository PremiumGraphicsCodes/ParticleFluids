#pragma once

#include "IPopupButton.h"
#include "../Math/Vector3d.h"

namespace Crystal {
	namespace UI {

class PositionSelectButton : public IPopupButton
{
public:
	PositionSelectButton(const std::string& name, Scene::RootScene* model, Canvas* canvas) :
		IPopupButton(name, model, canvas),
		position(0,0,0)
	{
	}

	void onShow() override;

	void onOk() override;

	void onCancel() override;

	Math::Vector3dd getPosition() const { return position; }

private:
	Math::Vector3df position;
};

	}
}