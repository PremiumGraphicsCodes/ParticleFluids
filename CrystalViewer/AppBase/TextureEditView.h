#pragma once

#include "IEditCancelView.h"
#include "IntView.h"
#include "FilePathView.h"

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

	IntView idView;
	FilePathView filePathView;
};

	}
}
