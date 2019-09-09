#pragma once

#include "IWindow.h"
#include "WireFrameView.h"
#include "IntView.h"
#include "StringView.h"
#include "../Scene/WireFrameScene.h"
#include "../Scene/World.h"
#include "Canvas.h"

namespace Crystal {
	namespace UI {

class WireFrameEditView : public IWindow
{
public:
	WireFrameEditView(const std::string& name, Scene::World* repository, Canvas* canvas);

	void onShow() override;

	void setValue(Scene::WireFrameScene* value);

private:
	WireFrameView wire;
	IntView id;
	StringView name;
};

	}
}
