#pragma once

#include "IPanel.h"
#include "../Math/Vector3d.h"

namespace Crystal {
	namespace UI {

class PositionSelectView : public IPanel
{
public:
	PositionSelectView(const std::string& name, Scene::RootScene* model, Canvas* canvas) :
		IPanel(name, model, canvas),
		position(0,0,0)
	{
	}

	void show() override;

	Math::Vector3dd getPosition() const { return position; }

private:
	Math::Vector3df position;
};

	}
}