#pragma once

#include "IPanel.h"

#include "IntView.h"
#include "Button.h"

namespace Crystal {
	namespace UI {

class ObjectSelectView : public IPanel
{
public:
	ObjectSelectView(const std::string& name, Scene::World* model, Canvas* canvas);

	ObjectSelectView(const std::string& name, Scene::World* model, Canvas* canvas, const Scene::SceneType type);

	int getId() const { return idView.getValue(); }

private:
	IntView idView;
	Button pickButton;
	Scene::SceneType type;
};

	}
}