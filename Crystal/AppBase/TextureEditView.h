#pragma once

#include "IWindow.h"
#include "TextureView.h"
#include "IntView.h"
#include "StringView.h"
#include "../Scene/TextureScene.h"
#include "../Scene/World.h"
#include "Canvas.h"

namespace Crystal {
	namespace UI {

class TextureEditView : public IWindow
{
public:
	TextureEditView(const std::string& name, Scene::World* repository, Canvas* canvas);

	void show() override;

	void setValue(Scene::TextureScene* value);

private:
	TextureView texture;
	IntView id;
	StringView name;
};

	}
}
