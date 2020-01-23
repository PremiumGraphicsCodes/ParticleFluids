#pragma once

#include "IEditCancelView.h"
#include "TextureView.h"
#include "IntView.h"

namespace Crystal {
	namespace Scene {
		class TextureScene;
	}
	namespace UI {

class TextureEditView : public IEditCancelView
{
public:
	explicit TextureEditView(const std::string& name, Scene::World* world, Canvas* canvas);

	void setValue(Scene::TextureScene* value);

private:
	void onEdit() override;

	TextureView texture;
	IntView id;
	StringView name;
};

	}
}
